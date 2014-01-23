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
#define BACKGROUND  12
#define FOREGROUND  13

//#define DEBUG
//#define MESSAGE_ON
#define   STL_LIST

class PlayThread : public QThread
{
    Q_OBJECT

public:
    PlayThread();
#ifndef STL_LIST
    PlayThread(QLabel* iLabel, QLabel* dLabel, QList<QImage>* iBuf, QList<QImage>* gBuf, QList<QImage>* dBuf, QList<QImage>* bBuf, QTimer* timer_ptr, int* fps);
    PlayThread(QLabel* iLabel, QLabel* dLabel, QList<QImage>* iBuf, QList<QImage>* gBuf, QList<QImage>* dBuf, QList<QImage>* bBuf, int* fps);
#else
    PlayThread(QLabel* iLabel, QLabel* dLabel, list<QImage>* stl_iBuf, list<QImage>* stl_gBuf, list<QImage>* stl_dBuf, list<QImage>* stl_bBuf, QTimer* timer_ptr, int* fps);
    PlayThread(QLabel* iLabel, QLabel* dLabel, list<QImage>* stl_iBuf, list<QImage>* stl_gBuf, list<QImage>* stl_dBuf, list<QImage>* stl_bBuf, int* fps);
#endif
    virtual ~PlayThread(){};
    virtual void run();

    void play();
    void stop_play();

    QString get_status();
    int     state();
    int     label();
    void    set_label(int lbl);
    void    update_frame_ctr(int position);
    int     get_frame_ctr();

    QMutex mutex;

private:
    QLabel* imgLabel;
    QLabel* dbgLabel;
#ifndef STL_LIST
    QList<QImage>* imgBuffer;
    QList<QImage>* gryBuffer;
    QList<QImage>* dbgBuffer;
    QList<QImage>* backBuffer;
#else
    std::list<QImage>* imgBuffer;
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

private slots:
    void imageUpdate();
};

#endif // PLAYTHREAD_H
