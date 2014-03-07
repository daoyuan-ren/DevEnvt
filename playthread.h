#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <iostream>
#include <QThread>
#include <QLabel>
#include <QTimer>
#include <QMutex>
#include <QMainWindow>

using namespace std;

// define states of player
#define INIT        0
#define PLAYING     1
#define BUFFERING   2
#define STOPPED     3

//define the pictures to be shown
#define ORIGINAL    10
#define GREYSCALE   11
#define COLOR       12
#define BACKGROUND  13
#define FOREGROUND  14

//#define DEBUG
//#define MESSAGE_ON
#define   STL_LIST

class PlayThread : public QThread
{
    Q_OBJECT

public:
    PlayThread();
#ifdef STL_LIST
    PlayThread(QLabel* iLabel, QLabel* dLabel, list<QImage>* stl_iBuf, list<QImage>* stl_cBuf, list<QImage>* stl_gBuf, list<QImage>* stl_dBuf, list<QImage>* stl_bBuf, QTimer* timer_ptr, int* fps, bool lock_input);
    PlayThread(QLabel* iLabel, QLabel* dLabel, list<QImage>* stl_iBuf, list<QImage>* stl_cBuf, list<QImage>* stl_gBuf, list<QImage>* stl_dBuf, list<QImage>* stl_bBuf, int* fps, bool lock_input);
#endif
    virtual ~PlayThread(){};
    virtual void run();

    void play();
    void stop_play();

    QString get_status();
    int     state();
    int     label();
    void    set_label(int lbl);
    void    set_lock(bool lock_input);
    void    update_frame_ctr(int position);
    int     get_frame_ctr();
    int     get_fps(){return *fps;}

    QMutex mutex;

private:
    QLabel* imgLabel;
    QLabel* dbgLabel;
#ifdef STL_LIST
    std::list<QImage>* imgBuffer;
    std::list<QImage>* clrBuffer;
    std::list<QImage>* gryBuffer;
    std::list<QImage>* dbgBuffer;
    std::list<QImage>* backBuffer;
    std::list<QImage>  swap;
#endif
    QTimer* timer_ptr;
    QString status;


    int* fps;
    int frame_pos;
    unsigned int played_frame_cnt;
    int state_t;
    int label_t;
    bool lock_input;

private slots:
    void imageUpdate();
};

#endif // PLAYTHREAD_H
