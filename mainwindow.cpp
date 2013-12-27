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
    movie       = NULL;
    pixMap      = NULL;
    frame_ctr   = 0;
    fps         = ui->fps_spinBox->value();
    width       = 0;
    height      = 0;
    fps_str     = "";
    status_str  = "";
    interval.tv_sec  = 0;
    interval.tv_nsec = 50000000L;

    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(imageUpdate()));
    player = new PlayThread(ui->label, ui->label_debug, &imgBuffer, &dbgBuffer, timer, &fps, &frame_ctr);
}

MainWindow::~MainWindow()
{
    timer->stop();
    delete timer;
    delete ui;
    exit(0);
}

void MainWindow::on_pushButton_select_clicked()
{
    bool    isPlaying  = false;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        if(cap.isOpened()){
            cap.release();
        }
        cap.open(fileName.toStdString());
        //cap.open("/home/ren/Videos/output_30.avi");
        fps     = cap.get(CV_CAP_PROP_FPS);
        width   = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        height  = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

        Mat frame, back, fore;
        QImage image, grey_image;
        vector< vector<Point> > contours;
        vector< vector<Point> > bigcons;
        BackgroundSubtractorMOG2 bg;
        bg.set("nmixtures", 3);
        bg.set("history", 96);

        for(int i = 0;; i++) {
            cap >> frame;
            image = Mat2QImage(frame);

            GaussianBlur(frame, frame, Size(7, 7), 1.5, 1.5);
            bg.operator ()(frame, fore);
            bg.getBackgroundImage(back);
            erode(fore, fore, cv::Mat());
            dilate(fore, fore, cv::Mat());
            {

//                cv::findContours(fore, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
//                bigcons.clear();
//                for(int i = 0; i < contours.size(); i++){
//                    if(contours.at(i).size() > 200) {
//                        bigcons.push_back(contours.at(i));
//                    }
//                }
//                cv::drawContours(frame, bigcons, -1, cv::Scalar(0, 255, 0), 2);
//                QImage grey_image(fore.data, frame.cols, frame.rows, QImage::Format_Indexed8);
            }
            grey_image = Mat2QImage(fore);
            imgBuffer.append(image);
            dbgBuffer.append(grey_image);

//            imshow("frame", frame);
//            imshow("fore", fore);
//            cout << "fore: " << i << endl;

            ui->lcdNumber_buffer->display(imgBuffer.length()-frame_ctr);
            nanosleep(&interval, NULL);
            if(waitKey(30) >= 0){
                stop();
                isPlaying = false;
                break;
            }
            if(isPlaying == false){
//                play();
                player->start();
                isPlaying = true;
            }
        }
   }
   player->wait();
}

void MainWindow::on_actionOpen_triggered()
{
    bool    isPlaying  = false;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        if(cap.isOpened()){
            cap.release();
        }
        cap.open(fileName.toStdString());
        //cap.open("/home/ren/Videos/output_30.avi");
        width   = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        height  = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

        Mat frame, back, fore;
        QImage image, grey_image;
        vector< vector<Point> > contours;
        vector< vector<Point> > bigcons;
        BackgroundSubtractorMOG2 bg;
        bg.set("nmixtures", 3);
        bg.set("history", 96);

        for(int i = 0;; i++) {
            cap >> frame;
            image = Mat2QImage(frame);

            GaussianBlur(frame, frame, Size(7, 7), 1.5, 1.5);
            bg.operator ()(frame, fore);
            bg.getBackgroundImage(back);
            erode(fore, fore, cv::Mat());
            dilate(fore, fore, cv::Mat());
            {

//                cv::findContours(fore, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
//                bigcons.clear();
//                for(int i = 0; i < contours.size(); i++){
//                    if(contours.at(i).size() > 200) {
//                        bigcons.push_back(contours.at(i));
//                    }
//                }
//                cv::drawContours(frame, bigcons, -1, cv::Scalar(0, 255, 0), 2);
//                QImage grey_image(fore.data, frame.cols, frame.rows, QImage::Format_Indexed8);
            }
            grey_image = Mat2QImage(fore);
            imgBuffer.append(image);
            dbgBuffer.append(grey_image);

//            imshow("frame", frame);
//            imshow("fore", fore);
//            cout << "fore: " << i << endl;

            nanosleep(&interval, NULL);
            if(waitKey(30) >= 0){
                stop();
                isPlaying = false;
                break;
            }
            if(isPlaying == false){
                play();
                isPlaying = true;
            }
        }
   }
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
    play();
}

void MainWindow::imageUpdate() {
    if(!imgBuffer.isEmpty()){
        ui->label->setPixmap(QPixmap::fromImage(imgBuffer.at(frame_ctr)));
        ui->label_debug->setPixmap(QPixmap::fromImage(dbgBuffer.at(frame_ctr)));
        imgBuffer.removeFirst();
        dbgBuffer.removeFirst();
    }
    else
        cout << "image buffer empty" << endl;

    if(imgBuffer.length() - frame_ctr <= 0) {
        stop();
        ui->label_status->setText(QString::fromStdString("Buffering"));
        cout << "video buffering" << endl;
    }
    ui->label_fps->setText(QString::number(fps));
    cout << "[" << fps << "]" << " [" << width  << ", " << height << "] " << "<" << frame_ctr << ", (";
    cout << imgBuffer.length() << ", " << dbgBuffer.length() << "), " << imgBuffer.length() - frame_ctr << ">" << endl;

    frame_ctr++;
}

void MainWindow::play(){
    fps = ui->fps_spinBox->value();
    timer->start(1000/fps);
    ui->label_status->setText(QString::fromStdString("Playing"));
}

void *MainWindow::play_function(void *arg) {
    fps = ui->fps_spinBox->value();
    timer->start(1000/fps);
    ui->label_status->setText(QString::fromStdString("Playing"));
}

void MainWindow::stop(){
    timer->stop();
}

void MainWindow::on_actionQuit_triggered()
{
    timer->stop();
    delete timer;
    delete ui;
    exit(0);
}
