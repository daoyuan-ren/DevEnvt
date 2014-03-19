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

#ifdef STL_LIST
PlayThread::PlayThread(QLabel* iLabel, QLabel* dLabel, ROIDialog* roi_ui, list<QImage>* stl_iBuf, list<QImage>* stl_cBuf, list<QImage>* stl_gBuf, list<QImage>* stl_dBuf, list<QImage>* stl_bBuf, list<vector<QImage> >* stl_roiBuf, QTimer* timer, int* fps, bool lock_input)
{
    imgLabel    = (CamLabel*)iLabel;
    dbgLabel    = dLabel;
    imgBuffer   = stl_iBuf;
    clrBuffer   = stl_cBuf;
    gryBuffer   = stl_gBuf;
    dbgBuffer   = stl_dBuf;
    backBuffer  = stl_bBuf;
    roiBuffer   = stl_roiBuf;

    this->roi_ui = roi_ui;
    this->fps   = fps;
    frame_pos   = 0;
    played_frame_cnt    = 0;
    state_t     = INIT;
    label_t     = COLOR;
    status      = QString::fromStdString("No Input Video");
    timer_ptr   = timer;
    this->lock_input = lock_input;
}

PlayThread::PlayThread(QLabel* iLabel, QLabel* dLabel, ROIDialog* roi_ui, list<QImage>* stl_iBuf, list<QImage>* stl_cBuf, list<QImage>* stl_gBuf, list<QImage>* stl_dBuf, list<QImage>* stl_bBuf, list<vector<QImage> >* stl_roiBuf, int* fps, bool lock_input)
{
    imgLabel    = (CamLabel*)iLabel;
    dbgLabel    = dLabel;
    imgBuffer   = stl_iBuf;
    clrBuffer   = stl_cBuf;
    gryBuffer   = stl_gBuf;
    dbgBuffer   = stl_dBuf;
    backBuffer  = stl_bBuf;
    roiBuffer   = stl_roiBuf;

    this->roi_ui = roi_ui;
    this->fps   = fps;
    frame_pos   = 0;
    played_frame_cnt    = 0;
    state_t     = INIT;
    label_t     = COLOR;
    status      = QString::fromStdString("No Input Video");
    timer_ptr   = new QTimer(0);
    connect(timer_ptr, SIGNAL(timeout()), this, SLOT(imageUpdate()));
    this->lock_input = lock_input;
}
#endif

void PlayThread::run() {
#ifdef MESSAGE_ON
    cout << "start to play" << endl;
    cout << "@player.run(): " << currentThreadId() << endl;
#endif
    play();
}

#ifdef STL_LIST
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

        if(lock_input == true){
            QPixmap lock_screen((*i_itr).width(),(*i_itr).height());
            lock_screen.fill(Qt::black);
            imgLabel->setPixmap(lock_screen);
        }
        else
            //imgLabel->setPixmap(QPixmap::fromImage(*i_itr).scaled(imgLabel->width(), imgLabel->height()));
            imgLabel->setImage((*i_itr).scaled(imgLabel->width(), imgLabel->height()));
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
    if(roi_ui != NULL && roi_ui->isVisible() && !roiBuffer->empty()){
        list<vector<QImage> >::iterator roi_itr = roiBuffer->begin();
        advance(roi_itr, frame_pos);
        if(!(*roi_itr).empty()){
            vector<QImage>::iterator vec_itr = (*roi_itr).begin();
            for(int i = 0; i < 4 && vec_itr!=(*roi_itr).end();i++){
                roi_ui->setImage(*vec_itr, i);
                vec_itr++;
            }
        } else {
            //roi_ui->setImage();
        }
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

void PlayThread::set_lock(bool lock_input){
    this->lock_input = lock_input;
}
