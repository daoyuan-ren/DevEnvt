#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <iostream>
#include <QThread>
#include <QLabel>
#include <QTimer>
//#include "mainwindow.h"

using namespace std;

class PlayThread : public QThread
{
public:
    PlayThread();
    PlayThread(QLabel* iLabel, QLabel* dLabel, QList<QImage>* iBuf, QList<QImage>* dBuf, QTimer* timer_ptr, int* fps, int* ctr);
    virtual void run();

protected:
    void play();
    void stop_play();

private:
    QLabel* imgLabel;
    QLabel* dbgLabel;
    QList<QImage>* imgBuffer;
    QList<QImage>* dbgBuffer;
    QTimer* timer_ptr;

    int* fps;
    int* frame_ctr;

private slots:
    void imageUpdate();
};

#endif // PLAYTHREAD_H
