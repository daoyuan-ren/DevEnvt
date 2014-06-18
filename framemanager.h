#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <QThread>
#include <QTimer>
#include <QImage>
#include <QSpinBox>
#include <QLabel>
#include <QMutex>

#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <iostream>

#include "blober.h"
#include "package_bgs/lb/LBMixtureOfGaussians.h"

using namespace cv;
using namespace std;

#define BLOB_ON
#define LABEL_ON

#define OP_BLACK        0
#define OP_BLUR         1
#define OP_SILOUETTE    2
#define OP_EDGE         3
#define OP_POLY         4
#define OP_MOSAIC       5
#define OP_DEFAULT      9

#define ST_INIT     10
#define ST_PROC     11
#define ST_STOP     12

//define the pictures to be shown
#define ORIGINAL    20
#define GREYSCALE   21
#define COLOR       22
#define BACKGROUND  23
#define FOREGROUND  24
#define DEBUG       29

#define OPENCV_MD   30
#define MIXGAU_MD   31

#define HISTORY     156

class FrameManager : public QThread
{
    Q_OBJECT
public:
    explicit FrameManager(QObject *parent = 0);
    FrameManager(VideoCapture cap, VideoWriter wtr, QSpinBox* spinBox_ctSize,
                 QLabel* imgLabel, QLabel* dbgLabel, QImage* s_back = NULL);
    ~FrameManager();

    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);

//    void process();
    void black_out(Mat& st_back, Mat& st_back_grey);
    void blur(Mat& mat, const Mat& fore, Mat& grey, Mat& st_back, Mat& st_back_grey);
    void poly(Mat& st_back, Mat& st_back_grey, Scalar color = CL_BLUE);
    void mosaic(Mat &mat, Mat& grey, Mat &st_back, Mat& st_back_grey);
    void edge(Mat& fore, Mat& grey, const Mat& back, const Mat& grey_back, Mat& st_back, Mat& st_back_grey);
    void silouette(const Mat& fore, const Mat& back, const Mat& grey_back, Mat& st_back, Mat& st_back_grey);
    void rgbCut(Mat& fore, const Mat& back, const Mat& st_back, unsigned char thresh);

    void gamma_correction(Mat& mat, const double gamma);
    unsigned int frameIndex();

    void inPrivacy(bool privacy_mode);
    void pain_rect(bool paint_blob);
    void shadow(bool shadow_detect);
    void setShape(bool with_shape);
    void setGreyROI(bool grey_roi);
    void setErosion(bool erosion);
    void setDilate(bool dilation);
    void setOperat(int operation);
    void setState(int state_t);
    void setAcuracy(int acuracy);
    void setMosaicSize(int mosaic_size);
    void setSigma(double gau_sigma);
    void setGauSize(int gau_size);
    void setEdgeThd(int edge_thd);
    void setLabel(int lbl);
    void setDetector(int working_md);
    void setRGBThd(int rgbThd);
    void setEroType(int type);
    void setEroSize(int size);
    void setDilType(int type);
    void setDilSize(int size);
    void setRecord(bool record);

    int  state();
    int  label();
    int  motionDetector();

    int  bgModelSensitivity();
    int  bgModelLearnRate();
    int  bgModelNoiseVar();
    int  bgModelBgThreshold();

    QString message();
    void    addMessage(QString message);
    void    clearMessage();

    virtual void run();

    QMutex msgMutex;
private:
    bool in_privacy_mode;
    bool pain_blob;
    bool shadow_detect;
    bool with_shape;
    bool grey_roi;
    bool erosion;
    bool dilation;
    bool record;
    int  pixel_operation;
    int  label_t;
    int  state_t;
    int  edge_thd;
    int  rgb_thd;
    int  poly_acuracy;
    int  mosaic_size;
    int  gau_size;
    int  ero_size;
    int  ero_type;
    int  dil_size;
    int  dil_type;
    int  working_md;
    double gau_sigma;
    unsigned int frame_idx;

    timespec interval;
    QSpinBox* spinBox_ctSize;
    QLabel* imgLabel;
    QLabel* dbgLabel;
    QString runningMessage;

    QImage* static_background;
    VideoCapture cap;
    VideoWriter wtr;
    BackgroundSubtractorMOG2 bg;
    LBMixtureOfGaussians* bgs;

    Blober blober;

signals:
    void processFinished(QImage image, QImage dbgImage);
public slots:
    void process();
};

#endif // FRAMEMANAGER_H
