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
#define LABEL_ON

#define OP_BLACK    0
#define OP_BLUR     1
#define OP_BORDER   2
#define OP_EDGE     3
#define OP_DEFAULT  9

class FrameManager : public QThread
{
    Q_OBJECT
public:
    explicit FrameManager(QObject *parent = 0);
    FrameManager(VideoCapture cap, QList<QImage>* iBuf, QList<QImage>* gBuf, QList<QImage>* dBuf, QList<QImage>* bBuf, PlayThread* player, QSpinBox* spinBox_ctSize, QImage* s_back = NULL);

    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);

    void process();
    void black_out(Mat& st_back);
    void blur(Mat& mat, Mat& st_back);
    void edge(Mat& mat, const Mat& back, Mat& st_back);
    void border(Mat& mat,const Mat& fore, const Mat& back, Mat& st_back);

    void gamma_correction(Mat& mat, const double gamma);
    unsigned int buffered_frame();

    void inPrivacy(bool privacy_mode);
    void pain_rect(bool paint_blob);
    void setOperat(int operation);

    virtual void run();
private:
    bool in_privacy_mode;
    bool pain_blob;
    int pixel_operation;
    unsigned int buffered_frame_idx;

    timespec interval;
    QTimer* timer;
    QSpinBox* spinBox_ctSize;

    QImage* static_background;
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
