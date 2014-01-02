#include "playthread.h"

PlayThread::PlayThread()
{
    imgLabel            = NULL;
    dbgLabel            = NULL;
    imgBuffer           = NULL;
    dbgBuffer           = NULL;
    backBuffer          = NULL;
    timer_ptr           = NULL;
    fps                 = NULL;
    frame_pos           = 0;
    played_frame_cnt    = 0;
    state_t             = INIT;
    label_t             = FOREGROUND;
    status              = QString::fromStdString("No Input Video");
}

PlayThread::PlayThread(QLabel* iLabel, QLabel* dLabel, QList<QImage>* iBuf, QList<QImage>* dBuf, QList<QImage>* bBuf, QTimer* timer, int* fps)
{
    imgLabel    = iLabel;
    dbgLabel    = dLabel;
    imgBuffer   = iBuf;
    dbgBuffer   = dBuf;
    backBuffer  = bBuf;
    this->fps   = fps;
    frame_pos   = 0;
    played_frame_cnt    = 0;
    state_t     = INIT;
    label_t     = FOREGROUND;
    status      = QString::fromStdString("No Input Video");
    timer_ptr   = timer;
}

PlayThread::PlayThread(QLabel* iLabel, QLabel* dLabel, QList<QImage>* iBuf, QList<QImage>* dBuf, QList<QImage>* bBuf, int* fps)
{
    imgLabel    = iLabel;
    dbgLabel    = dLabel;
    imgBuffer   = iBuf;
    dbgBuffer   = dBuf;
    backBuffer  = bBuf;
    this->fps   = fps;
    frame_pos   = 0;
    played_frame_cnt    = 0;
    state_t     = INIT;
    label_t     = FOREGROUND;
    status      = QString::fromStdString("No Input Video");
    timer_ptr   = new QTimer(0);
    connect(timer_ptr, SIGNAL(timeout()), this, SLOT(imageUpdate()));
}

void PlayThread::run() {
#ifdef DEBUG
    cout << "start to play" << endl;
    cout << "@player.run(): " << currentThreadId() << endl;
#endif
    play();
}

void PlayThread::imageUpdate() {
#ifdef DEBUG
    cout << "@player.imageUpdate(): " << currentThreadId() << endl;
#endif
    mutex.lock();
    if(imgBuffer->length() - frame_pos <= 0) {
        stop_play();
        state_t = BUFFERING;
        status  = QString::fromStdString("Buffering");
//        ui->label_status->setText(QString::fromStdString("Buffering"));
#ifdef DEBUG
        cout << "video buffering" << endl;
#endif
    } else if(!imgBuffer->isEmpty()){
        imgLabel->setPixmap(QPixmap::fromImage(imgBuffer->at(frame_pos)));
        switch(label_t){
        case ORIGINAL:
            dbgLabel->setPixmap(QPixmap::fromImage(imgBuffer->at(frame_pos)));
            break;
        case GREYSCALE:
            // todo: image transformation
            dbgLabel->setPixmap(QPixmap::fromImage(imgBuffer->at(frame_pos)));
            break;
        case BACKGROUND:
            dbgLabel->setPixmap(QPixmap::fromImage(backBuffer->at(frame_pos)));
            break;
        case FOREGROUND:
            dbgLabel->setPixmap(QPixmap::fromImage(dbgBuffer->at(frame_pos)));
            break;
        default:
            break;
        }
//        imgBuffer->removeFirst();
//        dbgBuffer->removeFirst();
    }
    else{
        status  = QString::fromStdString("Buffering");
#ifdef DEBUG
        cout << "image buffer empty" << endl;
#endif
    }
#ifdef DEBUG
    time_t now = time(NULL);
    cout << now%60 << ": [" << *fps << "]" <<  "<" << played_frame_cnt++ << ", (";
    cout << imgBuffer->length() << ", " << dbgBuffer->length() << "), " << imgBuffer->length() - frame_pos << ">" << endl;    
#endif
    frame_pos++;
    mutex.unlock();
}

void PlayThread::play(){
#ifdef DEBUG
    cout << "@player.play(): " << currentThreadId() << endl;
#endif
    timer_ptr->start(1000 / *fps);
    state_t = PLAYING;
    status = QString::fromStdString("Playing");
}

void PlayThread::stop_play(){
    timer_ptr->stop();
    state_t = STOPPED;
    status = QString::fromStdString("Stopped");
}

QString PlayThread::get_status(){
    return status;
}

int PlayThread::get_frame_ctr(){
    return frame_pos;
}

int PlayThread::update_frame_ctr(int position){
    frame_pos = position;
}

int PlayThread::state(){
    return state_t;
}

int PlayThread::label(){
    return label_t;
}

void PlayThread::set_label(int lbl){
    label_t = lbl;
}
