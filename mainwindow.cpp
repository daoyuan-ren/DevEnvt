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
    background  = NULL;

    fps_str     = "";
    status_str  = "";
    interval.tv_sec  = 3;
    interval.tv_nsec = 500000000L; //1 000 000 000nsec = 1sec

    fmanager = NULL;

    //clock used to update the label in ui
    lup_timer = new QTimer(this);
    connect(lup_timer, SIGNAL(timeout()), this, SLOT(labelUpdate()));    
}

MainWindow::~MainWindow()
{
    if(fmanager != NULL){
        fmanager->terminate();
        fmanager->quit();
    }

    delete fmanager;
    delete ui;
    exit(0);
}

void MainWindow::on_pushButton_select_clicked()
{
    QFileDialog dialog;

    //QString fileName = dialog.getOpenFileName(this, tr("Open File"), QDir::currentPath(),tr("Videos(*.avi)"));
    QString fileName = dialog.getOpenFileName(this, tr("Open File"), "/home/ren/Videos",tr("Videos(*.avi *.avi.ln)"));
    if(fileName.isEmpty())
        return;

    if(dialog.close() == true)
        process(fileName,false);
}

void MainWindow::setBackground(QImage *background){
    this->background = background;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/ren/Videos",tr("Videos(*.avi *.avi.ln)"));
    if(fileName.isEmpty())
        return;
    process(fileName, false);
}

/************* replaced by FrameManager.Mat2QImage() ***********************
#ifndef FMANAGER
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
#endif
*/
/************* replaced by FrameManager.QImage2Mat() ***********************
#ifndef FMANAGER
cv::Mat MainWindow::QImage2Mat(QImage const& src)
{
     cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cvtColor(tmp, result,CV_BGR2RGB);
     return result;
}
#endif
*/
void MainWindow::on_pushButton_apply_clicked()
{
    if(!cap.isOpened())
        return;
    fps = ui->fps_spinBox->value();
}

/************* replaced by Player.imageUpdate() ***********************
#ifndef PLAYER

void MainWindow::imageUpdate() {
#ifdef MESSAGE_ON
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
#endif
*/
/************* replaced by Player.play() ******************************
#ifndef PLAYER
void MainWindow::play(){
#ifdef MESSAGE_ON
            cout << "@MainWindow.play(): 1" << endl;
#endif
    fps = ui->fps_spinBox->value();
    mem_timer->start(1000/10);
    ui->label_status->setText(QString::fromStdString("Playing"));
}
#endif
*/
/************* replaced by Player.play() ******************************
#ifndef PLAYER
void *MainWindow::play_function(void *arg) {
    fps = ui->fps_spinBox->value();
    mem_timer->start(1000/fps);
    ui->label_status->setText(QString::fromStdString("Playing"));
}
#endif
*/
/************* replaced by Player.stop_play() *************************
#ifndef PLAYER
void MainWindow::stop(){
    mem_timer->stop();
}
#endif
*/
void MainWindow::on_actionQuit_triggered()
{
    delete ui;
    exit(0);
}

void MainWindow::process(QString fileName, bool live){

    if(live == false) {
        if(cap.isOpened()){
            cap.release();
            if(fmanager != NULL){
                fmanager->quit();
                delete fmanager;
            }
        }
        cap.open(fileName.toStdString());
    }
    if(live == true) {
        if(cap.isOpened()){
            cap.release();
            if(fmanager != NULL){
                delete fmanager;
            }
        }
        cap.open(0);
    }

    if(cap.isOpened()){
        fmanager = new FrameManager(cap, ui->spinBox_ctSize, ui->label, ui->label_debug, background);
        connect(fmanager, SIGNAL(processFinished(QImage, QImage)), this, SLOT(imageUpdate(QImage, QImage)));

        fmanager->inPrivacy(ui->checkBox_privacy->isChecked());
        fmanager->pain_rect(ui->checkBox_rect->isChecked());
        if(ui->radioButton_black->isChecked())
            fmanager->setOperat(OP_BLACK);
        else if(ui->radioButton_blur->isChecked())
            fmanager->setOperat(OP_BLUR);
        else if(ui->radioButton_border->isChecked())
            fmanager->setOperat(OP_BORDER);
        else if(ui->radioButton_edge->isChecked())
            fmanager->setOperat(OP_EDGE);
        else if(ui->radioButton_mosaic->isChecked())
            fmanager->setOperat(OP_MOSAIC);
        else if(ui->radioButton_poly->isChecked())
            fmanager->setOperat(OP_POLY);
        else
            fmanager->setOperat(OP_DEFAULT);
        fmanager->start(QThread::NormalPriority);
        //player->start(QThread::HighPriority);
        lup_timer->start(500);
    }
}

void MainWindow::on_toolButton_play_clicked()
{
    if(fmanager->state() == ST_STOP)
        fmanager->start();
}

void MainWindow::on_toolButton_stop_clicked()
{
    if(fmanager->state() != ST_STOP)
        fmanager->terminate();
}

void MainWindow::on_pushButton_live_clicked()
{
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
    if(fmanager != NULL)
        fmanager->setLabel(FOREGROUND);
}

void MainWindow::on_radioButton_back_clicked()
{
    if(fmanager != NULL)
        fmanager->setLabel(BACKGROUND);
}

void MainWindow::on_radioButton_grey_clicked()
{
    if(fmanager != NULL)
        fmanager->setLabel(GREYSCALE);
}

void MainWindow::on_radioButton_orig_clicked()
{
    if(fmanager != NULL)
        fmanager->setLabel(ORIGINAL);
}

//void MainWindow::memManage(){
//#ifdef MESSAGE_ON
//            cout << "@MainWindow.memManage(): 1" << endl;
//#endif
//            std::list<QImage>::iterator beg, end;
//            if(player->get_frame_ctr() > 30){
//                player->mutex.lock();
//                beg = imgBuffer->begin();
//                end = imgBuffer->end();
//                advance(end, player->get_frame_ctr());

//                imgBuffer->erase(beg, end);
//#ifdef MESSAGE_ON
//                cout << "new allocated iBuffer with size " << imgBuffer->size() << endl;
//#endif
//                beg = clrBuffer->begin();
//                end = clrBuffer->end();
//                advance(end, player->get_frame_ctr());
//                clrBuffer->erase(beg, end);
//#ifdef MESSAGE_ON
//                cout << "new allocated cBuffer with size " << clrBuffer->size() << endl;
//#endif
//                beg = gryBuffer->begin();
//                end = gryBuffer->end();
//                advance(end, player->get_frame_ctr());
//                gryBuffer->erase(beg, end);
//#ifdef MESSAGE_ON
//                cout << "new allocated gBuffer with size " << gryBuffer->size() << endl;
//#endif
//                beg = dbgBuffer->begin();
//                end = dbgBuffer->end();
//                advance(end, player->get_frame_ctr());
//                dbgBuffer->erase(beg, end);
//#ifdef MESSAGE_ON
//                cout << "new allocated dBuffer with size " << dbgBuffer->size() << endl;
//#endif
//                beg = backBuffer->begin();
//                end = backBuffer->end();
//                advance(end, player->get_frame_ctr());
//                backBuffer->erase(beg, end);
//#ifdef MESSAGE_ON
//                cout << "new allocated bBuffer with size " << backBuffer->size() << endl;
//#endif
//                alloc_idx = player->get_frame_ctr();
//                player->update_frame_ctr(0);
//                player->mutex.unlock();
//            }
//}

void MainWindow::labelUpdate(){
#ifdef MESSAGE_ON
            cout << "@MainWindow.labelUpdate(): 1" << endl;
#endif
    ui->label_fps->setText(QString::number(fps));
    ui->lcdNumber_buffer->display(0);
    ui->label_status->setText("unknown");
    return;
}

void MainWindow::imageUpdate(QImage image, QImage dbgImage) {
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label_debug->setPixmap(QPixmap::fromImage(dbgImage));
}

void MainWindow::on_checkBox_privacy_clicked()
{
    if(fmanager != NULL){
        fmanager->inPrivacy(ui->checkBox_privacy->isChecked());
    }
    return;
}

void MainWindow::on_radioButton_black_clicked()
{
    if(fmanager != NULL)
        fmanager->setOperat(OP_BLACK);
    return;
}

void MainWindow::on_radioButton_blur_clicked()
{
    if(fmanager != NULL)
        fmanager->setOperat(OP_BLUR);
    return;
}

void MainWindow::on_radioButton_edge_clicked()
{
    if(fmanager != NULL)
        fmanager->setOperat(OP_EDGE);
    return;
}

void MainWindow::on_radioButton_border_clicked()
{
    if(fmanager != NULL)
        fmanager->setOperat(OP_BORDER);
}

void MainWindow::on_actionOpen_Background_triggered()
{
    QFileDialog dialog;
    QString fileName = dialog.getOpenFileName(this, tr("Open File"), "/home/ren/Videos", tr("Images(*.png *.jpg *.tiff)"));
    if(fileName.isEmpty())
        return;
    background = new QImage(fileName);
    return;
}

void MainWindow::on_radioButton_default_clicked()
{
    if(fmanager != NULL)
        fmanager->setOperat(OP_DEFAULT);
    return;
}

void MainWindow::on_checkBox_rect_clicked()
{
    if(fmanager != NULL)
        fmanager->pain_rect(ui->checkBox_rect->isChecked());
    return;
}

void MainWindow::on_radioButton_mosaic_clicked()
{
    if(fmanager != NULL)
        fmanager->setOperat(OP_MOSAIC);
    return;
}

void MainWindow::on_checkBox_shadow_clicked()
{
    if(fmanager != NULL)
        fmanager->shadow(ui->checkBox_shadow->isChecked());
    return;
}

void MainWindow::on_pushButton_work_clicked()
{
    if(fmanager != NULL){
        if(fmanager->state() == ST_PROC){
            fmanager->setState(ST_STOP);
            ui->pushButton_work->setText(QString::fromStdString("Work"));

        } else {
            fmanager->setState(ST_PROC);
            ui->pushButton_work->setText(QString::fromStdString("Halt"));
        }
    }
    return;
}

void MainWindow::on_radioButton_poly_clicked()
{
    if(fmanager != NULL){
        fmanager->setOperat(OP_POLY);
    }
}

void MainWindow::on_actionLIVE_triggered()
{
    process(QString::fromStdString(""), true);
}

void MainWindow::on_spinBox_polyAcy_valueChanged(int arg1)
{
    if(fmanager != NULL){
        fmanager->setAcuracy(ui->spinBox_polyAcy->value());
    }
}

void MainWindow::on_spinBox_moasicSize_valueChanged(int arg1)
{
    if(fmanager != NULL){
        fmanager->setMosaicSize(ui->spinBox_moasicSize->value());
    }
}

void MainWindow::on_doubleSpinBox_gauSigma_valueChanged(double arg1)
{
    if(fmanager != NULL){
        fmanager->setSigma(ui->doubleSpinBox_gauSigma->value());
    }
}

void MainWindow::on_radioButton_color_clicked()
{
        if(fmanager != NULL)
            fmanager->setLabel(COLOR);
}

void MainWindow::on_checkBox_shape_clicked()
{
    if(fmanager != NULL){
        fmanager->setShape(ui->checkBox_shape->isChecked());
    }

}

void MainWindow::on_spinBox_egThd_valueChanged(const QString &arg1)
{
    if(fmanager != NULL)
        fmanager->setEdgeThd(ui->spinBox_egThd->value());
}
