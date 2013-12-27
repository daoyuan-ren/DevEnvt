#include "playthread.h"

PlayThread::PlayThread()
{
    imgLabel    = NULL;
    dbgLabel    = NULL;
    imgBuffer   = NULL;
    dbgBuffer   = NULL;
    timer_ptr   = NULL;
    fps         = NULL;
    frame_ctr   = NULL;
}

PlayThread::PlayThread(QLabel* iLabel, QLabel* dLabel, QList<QImage>* iBuf, QList<QImage>* dBuf, QTimer* timer, int* fps, int* ctr)
{
    imgLabel    = iLabel;
    dbgLabel    = dLabel;
    imgBuffer   = iBuf;
    dbgBuffer   = dBuf;
    timer_ptr = timer;
    this->fps   = fps;
    frame_ctr   = ctr;
    connect(timer_ptr, SIGNAL(timeout()), this, SLOT(PlayThread::imageUpdate()));
}

void PlayThread::run() {
    play();
}

void PlayThread::imageUpdate() {
    if(!imgBuffer->isEmpty()){
        imgLabel->setPixmap(QPixmap::fromImage(imgBuffer->at(*frame_ctr)));
        dbgLabel->setPixmap(QPixmap::fromImage(dbgBuffer->at(*frame_ctr)));
        imgBuffer->removeFirst();
        dbgBuffer->removeFirst();
    }
    else
        cout << "image buffer empty" << endl;

//    if(imgBuffer->length() - *frame_ctr <= 0) {
//        stop_play();
//        ui->label_status->setText(QString::fromStdString("Buffering"));
//        cout << "video buffering" << endl;
//    }
//    ui->label_fps->setText(QString::number(*fps));
//    cout << "[" << fps << "]" << " [" << width  << ", " << height << "] " << "<" << frame_ctr << ", (";
//    cout << imgBuffer->length() << ", " << dbgBuffer->length() << "), " << imgBuffer->length() - *frame_ctr << ">" << endl;

    cout << "playing in thread" << endl;
    *frame_ctr++;
}

void PlayThread::play(){
//    *fps = Ui::MainWindow::ui->fps_spinBox->value();
    timer_ptr->start(1000 / *fps);
//    ui->label_status->setText(QString::fromStdString("Playing"));
}

void PlayThread::stop_play(){
    timer_ptr->stop();
}
