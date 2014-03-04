#include "playthread.h"

PlayThread::PlayThread()
{
    imgLabel            = NULL;
    dbgLabel            = NULL;
    imgBuffer           = NULL;
    gryBuffer           = NULL;
    dbgBuffer           = NULL;
    backBuffer          = NULL;
//#ifdef STL_LIST
//    stl_imgBuffer           = NULL;
//    stl_gryBuffer           = NULL;
//    stl_dbgBuffer           = NULL;
//    stl_backBuffer          = NULL;
//#endif
    timer_ptr           = NULL;
    fps                 = NULL;
    frame_pos           = 0;
    played_frame_cnt    = 0;
    state_t             = INIT;
    label_t             = GREYSCALE;
    status              = QString::fromStdString("No Input Video");
}

#ifndef STL_LIST
PlayThread::PlayThread(QLabel* iLabel, QLabel* dLabel, QList<QImage>* iBuf, QList<QImage>* gBuf, QList<QImage>* dBuf, QList<QImage>* bBuf, QTimer* timer, int* fps)
{
    imgLabel    = iLabel;
    dbgLabel    = dLabel;
    imgBuffer   = iBuf;
    gryBuffer   = gBuf;
    dbgBuffer   = dBuf;
    backBuffer  = bBuf;
    this->fps   = fps;
    frame_pos   = 0;
    played_frame_cnt    = 0;
    state_t     = INIT;
    label_t     = GREYSCALE;
    status      = QString::fromStdString("No Input Video");
    timer_ptr   = timer;
}

PlayThread::PlayThread(QLabel* iLabel, QLabel* dLabel, QList<QImage>* iBuf, QList<QImage>* gBuf, QList<QImage>* dBuf, QList<QImage>* bBuf, int* fps)
{
    imgLabel    = iLabel;
    dbgLabel    = dLabel;
    imgBuffer   = iBuf;
    gryBuffer   = gBuf;
    dbgBuffer   = dBuf;
    backBuffer  = bBuf;
    this->fps   = fps;
    frame_pos   = 0;
    played_frame_cnt    = 0;
    state_t     = INIT;
    label_t     = GREYSCALE;
    status      = QString::fromStdString("No Input Video");
    timer_ptr   = new QTimer(0);
    connect(timer_ptr, SIGNAL(timeout()), this, SLOT(imageUpdate()));
}
#else
PlayThread::PlayThread(QLabel* iLabel, QLabel* dLabel, list<QImage>* stl_iBuf, list<QImage>* stl_cBuf, list<QImage>* stl_gBuf, list<QImage>* stl_dBuf, list<QImage>* stl_bBuf, QTimer* timer, int* fps)
{
    imgLabel    = iLabel;
    dbgLabel    = dLabel;
    imgBuffer   = stl_iBuf;
    clrBuffer   = stl_cBuf;
    gryBuffer   = stl_gBuf;
    dbgBuffer   = stl_dBuf;
    backBuffer  = stl_bBuf;
    this->fps   = fps;
    frame_pos   = 0;
    played_frame_cnt    = 0;
    state_t     = INIT;
    label_t     = GREYSCALE;
    status      = QString::fromStdString("No Input Video");
    timer_ptr   = timer;
}

PlayThread::PlayThread(QLabel* iLabel, QLabel* dLabel, list<QImage>* stl_iBuf, list<QImage>* stl_cBuf, list<QImage>* stl_gBuf, list<QImage>* stl_dBuf, list<QImage>* stl_bBuf, int* fps)
{
    imgLabel    = iLabel;
    dbgLabel    = dLabel;
    imgBuffer   = stl_iBuf;
    clrBuffer   = stl_cBuf;
    gryBuffer   = stl_gBuf;
    dbgBuffer   = stl_dBuf;
    backBuffer  = stl_bBuf;
    this->fps   = fps;
    frame_pos   = 0;
    played_frame_cnt    = 0;
    state_t     = INIT;
    label_t     = GREYSCALE;
    status      = QString::fromStdString("No Input Video");
    timer_ptr   = new QTimer(0);
    connect(timer_ptr, SIGNAL(timeout()), this, SLOT(imageUpdate()));
}
#endif

void PlayThread::run() {
#ifdef MESSAGE_ON
    cout << "start to play" << endl;
    cout << "@player.run(): " << currentThreadId() << endl;
#endif
    play();
}

#ifndef STL_LIST
void PlayThread::imageUpdate() {
#ifdef MESSAGE_ON
    cout << "@player.imageUpdate(): " << currentThreadId() << endl;
#endif
    mutex.lock();
    if(imgBuffer->length() - frame_pos <= 0) {
        stop_play();
        state_t = BUFFERING;
        status  = QString::fromStdString("Buffering");
//        ui->label_status->setText(QString::fromStdString("Buffering"));
#ifdef MESSAGE_ON
        cout << "video buffering" << endl;
#endif
    } else if(!imgBuffer->isEmpty()){
        imgLabel->setPixmap(QPixmap::fromImage(imgBuffer->at(frame_pos)));
        switch(label_t){
        case ORIGINAL:
            dbgLabel->setPixmap(QPixmap::fromImage(imgBuffer->at(frame_pos)));
            break;
        case GREYSCALE:
            dbgLabel->setPixmap(QPixmap::fromImage(gryBuffer->at(frame_pos)));
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
#ifdef MESSAGE_ON
        cout << "image buffer empty" << endl;
#endif
    }
#ifdef MESSAGE_ON
    time_t now = time(NULL);
    cout << now%60 << ": [" << *fps << "]" <<  "<" << played_frame_cnt++ << ", (";
    cout << imgBuffer->length() << ", " << dbgBuffer->length() << "), " << imgBuffer->length() - frame_pos << ">" << endl;    
#endif
    frame_pos++;
    mutex.unlock();
}
#else
void PlayThread::imageUpdate() {
#ifdef MESSAGE_ON
    cout << "@player.imageUpdate(): " << currentThreadId() << endl;
#endif
    mutex.lock();
    if(imgBuffer->size() - frame_pos <= 0) {
        stop_play();
        state_t = BUFFERING;
        status  = QString::fromStdString("Buffering");
//        ui->label_status->setText(QString::fromStdString("Buffering"));
#ifdef MESSAGE_ON
        cout << "video buffering" << endl;
#endif
    } else if(!imgBuffer->empty()){
        list<QImage>::iterator i_itr, c_itr, g_itr, b_itr, d_itr;
        i_itr = imgBuffer->begin();
        c_itr = clrBuffer->begin();
        g_itr = gryBuffer->begin();
        b_itr = backBuffer->begin();
        d_itr = dbgBuffer->begin();
        advance(i_itr, frame_pos);
        advance(c_itr, frame_pos);
        advance(g_itr, frame_pos);
        advance(b_itr, frame_pos);
        advance(d_itr, frame_pos);

        imgLabel->setPixmap(QPixmap::fromImage(*i_itr));
        if((*i_itr).isNull()){
            cerr << "empty image @" << frame_pos << endl;
            frame_pos++;
            mutex.unlock();
            return;
        }

        switch(label_t){
        case ORIGINAL:
            dbgLabel->setPixmap(QPixmap::fromImage(*i_itr));
            break;
        case COLOR:
            dbgLabel->setPixmap(QPixmap::fromImage(*c_itr));
            break;
        case GREYSCALE:
            dbgLabel->setPixmap(QPixmap::fromImage(*g_itr));
            break;
        case BACKGROUND:
            dbgLabel->setPixmap(QPixmap::fromImage(*b_itr));
            break;
        case FOREGROUND:
            dbgLabel->setPixmap(QPixmap::fromImage(*d_itr));
            break;
        default:
            break;
        }
    } else {
        status  = QString::fromStdString("Buffering");
#ifdef MESSAGE_ON
        cout << "image buffer empty" << endl;
#endif
    }
#ifdef MESSAGE_ON
    time_t now = time(NULL);
    cout << now%60 << ": [" << *fps << "]" <<  "<" << played_frame_cnt++ << ", (";
    cout << imgBuffer->length() << ", " << dbgBuffer->length() << "), " << imgBuffer->length() - frame_pos << ">" << endl;
#endif
    frame_pos++;
    mutex.unlock();
}
#endif

void PlayThread::play(){
#ifdef MESSAGE_ON
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

void PlayThread::update_frame_ctr(int position){
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
