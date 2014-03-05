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
#define OP_POLY     4
#define OP_MOSAIC   5
#define OP_DEFAULT  9

#define ST_PROC     10
#define ST_STOP     11

#define HISTORY     156

class FrameManager : public QThread
{
    Q_OBJECT
public:
    explicit FrameManager(QObject *parent = 0);
#ifdef STL_LIST
    FrameManager(VideoCapture cap, list<QImage>* stl_iBuf, list<QImage>* stl_cBuf, list<QImage>* stl_gBuf, list<QImage>* stl_dBuf, list<QImage>* stl_bBuf, PlayThread* player, QSpinBox* spinBox_ctSize, QImage* s_back = NULL);
#endif

    ~FrameManager();

    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);

    void process();
    void black_out(Mat& st_back, Mat& st_back_grey);
    void blur(Mat& mat, const Mat& fore, Mat& grey, Mat& st_back, Mat& st_back_grey);
    void poly(Mat& st_back, Mat& st_back_grey, Scalar color = CL_BLUE);
    void mosaic(Mat &mat, Mat& grey, Mat &st_back, Mat& st_back_grey);
    void edge(Mat& mat, Mat& grey, const Mat& back, const Mat& grey_back, Mat& st_back, Mat& st_back_grey);
    void border(const Mat& fore, const Mat& back, const Mat& grey_back, Mat& st_back, Mat& st_back_grey);

    void gamma_correction(Mat& mat, const double gamma);
    unsigned int buffered_frame();

    void inPrivacy(bool privacy_mode);
    void pain_rect(bool paint_blob);
    void shadow(bool shadow_detect);
    void setShape(bool with_shape);
    void setOperat(int operation);
    void setState(int state_t);
    void setAcuracy(int acuracy);
    void setMosaicSize(int mosaic_size);
    void setSigma(double gau_sigma);
    void setEdgeThd(int edge_thd);


    int  state();

    virtual void run();
private:
    bool in_privacy_mode;
    bool pain_blob;
    bool shadow_detect;
    bool with_shape;
    int  pixel_operation;
    int  state_t;
    int  edge_thd;
    int  poly_acuracy;
    int  mosaic_size;
    double gau_sigma;
    unsigned int buffered_frame_idx;

    timespec interval;
    QTimer* timer;
    QSpinBox* spinBox_ctSize;

    QImage* static_background;
#ifdef STL_LIST
    std::list<QImage>* imgBuffer;
    std::list<QImage>* clrBuffer;
    std::list<QImage>* gryBuffer;
    std::list<QImage>* dbgBuffer;
    std::list<QImage>* backBuffer;
    std::list<QImage>  swap;
#endif

    VideoCapture cap;
    BackgroundSubtractorMOG2 bg;

    Blober blober;
    PlayThread* player;

signals:
    
public slots:
    
};

#endif // FRAMEMANAGER_H
