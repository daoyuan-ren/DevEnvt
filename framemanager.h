#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <QThread>
#include <QTimer>
#include <QImage>
#include <QSpinBox>

#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <iostream>

#include "blober.h"
#include "playthread.h"
using namespace cv;
using namespace std;

#define BLOB_ON

class FrameManager : public QThread
{
    Q_OBJECT
public:
    explicit FrameManager(QObject *parent = 0);
    FrameManager(VideoCapture cap, QList<QImage>* iBuf, QList<QImage>* gBuf, QList<QImage>* dBuf, QList<QImage>* bBuf, PlayThread* player, QSpinBox* spinBox_ctSize);

    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);

    void process();
    void black_out(Mat& mat);
    void blur(Mat& mat);
    void edge(Mat& mat, const Mat& back);
    unsigned int buffered_frame();

    virtual void run();
private:
    unsigned int buffered_frame_idx;

    timespec interval;
    QTimer* timer;
    QSpinBox* spinBox_ctSize;

    QList<QImage>* imgBuffer;
    QList<QImage>* gryBuffer;
    QList<QImage>* dbgBuffer;
    QList<QImage>* backBuffer;
    QList<QImage>  swap;

    VideoCapture cap;
    BackgroundSubtractorMOG2 bg;

    Blober blober;
    PlayThread* player;
signals:
    
public slots:
    
};

#endif // FRAMEMANAGER_H
