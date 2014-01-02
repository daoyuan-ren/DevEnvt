#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <unistd.h>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    frame_pos   = 0;
    fps         = ui->fps_spinBox->value();
    width       = 0;
    height      = 0;
    alloc_idx   = 0;
    imgBuffer   = new QList<QImage>();
    dbgBuffer   = new QList<QImage>();
    backBuffer  = new QList<QImage>();
    fps_str     = "";
    status_str  = "";
    interval.tv_sec  = 3;
    interval.tv_nsec = 500000000L; //1 000 000 000nsec = 1sec

    bg.set("nmixtures", 3);
    bg.set("history", 108);
//    bg.bShadowDetection = true;
    bg.set("detectShadows", true);

    mem_timer = new QTimer(this);
    connect(mem_timer, SIGNAL(timeout()), this, SLOT(memManage()));
    lup_timer = new QTimer(this);
    connect(lup_timer, SIGNAL(timeout()), this, SLOT(labelUpdate()));
    player = new PlayThread(ui->label, ui->label_debug, imgBuffer, dbgBuffer, backBuffer, &fps);
}

MainWindow::~MainWindow()
{
    player->wait();
    fmanager->wait();

    mem_timer->stop();
    delete player;
    delete fmanager;
    delete mem_timer;
    delete ui;
    exit(0);
}

void MainWindow::on_pushButton_select_clicked()
{
    QFileDialog dialog;
    QString fileName = dialog.getOpenFileName(this, tr("Open File"), QDir::currentPath());

//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if(dialog.close() == true)
        process(fileName,false);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    process(fileName, false);
}

QImage MainWindow::Mat2QImage(cv::Mat const& src)
{
    cv::Mat temp; // make the same cv::Mat
    QImage::Format format;
    if(src.channels() == 3){
     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
     format = QImage::Format_RGB888;
    } else {
        temp = src;
        format = QImage::Format_Indexed8;
    }
    QImage dest((uchar*) temp.data, temp.cols, temp.rows, temp.step, format);
    QImage dest2(dest);
    dest2.detach(); // enforce deep copy
    return dest2;
}

cv::Mat MainWindow::QImage2Mat(QImage const& src)
{
     cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cvtColor(tmp, result,CV_BGR2RGB);
     return result;
}

void MainWindow::on_pushButton_apply_clicked()
{
    if(!cap.isOpened())
        return;
    fps = ui->fps_spinBox->value();
    player->start();
}

/************* replaced by Player.imageUpdate() ************************/
void MainWindow::imageUpdate() {
#ifdef DEBUG
            cout << "@MainWindow.imageUpdate(): 1" << endl;
#endif
    player->mutex.lock();
    if(!imgBuffer->isEmpty() && frame_pos < imgBuffer->size()){
        ui->label->setPixmap(QPixmap::fromImage(imgBuffer->at(frame_pos)));
        ui->label_debug->setPixmap(QPixmap::fromImage(dbgBuffer->at(frame_pos)));
    }
    else
        cout << "image buffer empty" << endl;

    if(imgBuffer->length() - frame_pos <= 0) {
//        stop();
//        player->stop_play();
        ui->label_status->setText(QString::fromStdString("Buffering"));
        cout << "video buffering" << endl;
    }
    ui->label_fps->setText(QString::number(fps));
    cout << "[" << fps << "]" << " [" << cap.get(CV_CAP_PROP_FRAME_WIDTH)  << ", " << cap.get(CV_CAP_PROP_FRAME_HEIGHT) << "] " << "<" << frame_pos << ", (";
    cout << imgBuffer->length() << ", " << dbgBuffer->length() << "), " << imgBuffer->length() - frame_pos << ">" << endl;

    frame_pos++;
    player->mutex.unlock();
}

/************* replaced by Player.play() *******************************/
void MainWindow::play(){
#ifdef DEBUG
            cout << "@MainWindow.play(): 1" << endl;
#endif
    fps = ui->fps_spinBox->value();
    mem_timer->start(1000/10);
    ui->label_status->setText(QString::fromStdString("Playing"));
}

/************* replaced by Player.play() *******************************/
void *MainWindow::play_function(void *arg) {
    fps = ui->fps_spinBox->value();
    mem_timer->start(1000/fps);
    ui->label_status->setText(QString::fromStdString("Playing"));
}

/************* replaced by Player.stop_play() **************************/
void MainWindow::stop(){
    mem_timer->stop();
}

void MainWindow::on_actionQuit_triggered()
{
    player->stop_play();
//    delete timer;
    delete ui;
    exit(0);
}

void MainWindow::process(QString fileName, bool live){

    if(live == false && fileName.isEmpty()) {
        return;
    }
    if(live == false && !fileName.isEmpty()) {
        if(cap.isOpened())
            cap.release();
        cap.open(fileName.toStdString());
    }
    if(live == true) {
        if(cap.isOpened())
            cap.release();
        cap.open(0);
    }

    if(cap.isOpened()){
        fmanager = new FrameManager(cap, imgBuffer, dbgBuffer, backBuffer, player, ui->spinBox_ctSize);
        fmanager->start(QThread::NormalPriority);
        player->start(QThread::HighPriority);
        mem_timer->start(3000);
        lup_timer->start(300);
    }
}

void MainWindow::on_toolButton_play_clicked()
{
    if(player->state() != PLAYING)
        player->start();
}

void MainWindow::on_toolButton_stop_clicked()
{
    if(player->state() != STOPPED && player->state() != INIT)
        player->stop_play();
}

void MainWindow::on_pushButton_live_clicked()
{
    if(player->state() == PLAYING){
        player->stop_play();
    }
    process(QString::fromStdString(""), true);
}

/*
Blob MainWindow::findBlobs(Mat& frame, Mat& drawing, int blob_minSize){
    cv::findContours(frame, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    blobs.create(contours.size());

      for( int i = 0; i < contours.size(); i++ )
      {
          if(contours[i].size() >= blob_minSize){
              approxPolyDP( Mat(contours[i]), blobs.contours_poly[i], 3, true );
              blobs.boundRect[i] = boundingRect( Mat(blobs.contours_poly[i]) );
#ifdef CIRELE
              minEnclosingCircle( (Mat)contours_poly[i], blobs.center[i], blobs.radius[i] );
#endif
          }
      }

      for( int i = 0; i< contours.size(); i++ )
      {
#ifdef POLY
          drawContours( drawing, blobs.contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
#endif
          rectangle( drawing, blobs.boundRect[i].tl(), blobs.boundRect[i].br(), color, 2, 8, 0 );
#ifdef CIRCLE
          circle( drawing, blobs.center[i], (int)blobs.radius[i], color, 2, 8, 0 );
#endif
      }
}
*/
/*
void MainWindow::paintBlobs(QImage* frame, Blober& blober){
    for(int i = 0; i < blober.boundRect->size(); i++){
        QPainter* painter = new QPainter(frame); // sorry i forgot the "&"
        painter->setPen(Qt::white);
        painter->setFont(QFont("Arial", 12));
        string text = blober.drawText((*(blober.boundRect))[i].x, (*(blober.boundRect))[i].y, (*(blober.boundRect))[i].width, (*(blober.boundRect))[i].height);
        painter->drawText((*(blober.boundRect))[i].x, (*(blober.boundRect))[i].y, QString::fromStdString(text));
        delete painter;
    }
}
*/

void MainWindow::on_radioButton_fore_clicked()
{
    player->set_label(FOREGROUND);
}

void MainWindow::on_radioButton_back_clicked()
{
    player->set_label(BACKGROUND);
}

void MainWindow::on_radioButton_grey_clicked()
{
    player->set_label(GREYSCALE);
}

void MainWindow::on_radioButton_orig_clicked()
{
    player->set_label(ORIGINAL);
}

void MainWindow::memManage(){
#ifdef DEBUG
            cout << "@MainWindow.memManage(): 1" << endl;
#endif
            if(player->get_frame_ctr() > 30){
                player->mutex.lock();
                swap = imgBuffer->mid(player->get_frame_ctr());
                delete imgBuffer;
                imgBuffer = new QList<QImage>(swap);
#ifdef DEBUG
                cout << "new allocated iBuffer with size " << imgBuffer->size() << endl;
#endif
                swap = dbgBuffer->mid(player->get_frame_ctr());
                delete dbgBuffer;
                dbgBuffer = new QList<QImage>(swap);
#ifdef DEBUG
                cout << "new allocated dBuffer with size " << dbgBuffer->size() << endl;
#endif
                swap = backBuffer->mid(player->get_frame_ctr());
                delete backBuffer;
                backBuffer = new QList<QImage>(swap);
#ifdef DEBUG
                cout << "new allocated bBuffer with size " << backBuffer->size() << endl;
#endif
                alloc_idx = player->get_frame_ctr();
                player->update_frame_ctr(0);
                player->mutex.unlock();
            }
//            if(player->state() == INIT){
//                player->start();
//            }
//            nanosleep(&interval, NULL);
}

void MainWindow::labelUpdate(){
#ifdef DEBUG
            cout << "@MainWindow.labelUpdate(): 1" << endl;
#endif
    ui->label_fps->setText(QString::number(fps));
    player->mutex.lock();
    ui->lcdNumber_buffer->display(imgBuffer->length() - player->get_frame_ctr());
    player->mutex.unlock();
    ui->label_status->setText(player->get_status());
}
