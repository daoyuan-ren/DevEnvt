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
    FrameManager(VideoCapture cap, list<QImage>* stl_iBuf, list<QImage>* stl_cBuf, list<QImage>* stl_gBuf, list<QImage>* stl_dBuf, list<QImage>* stl_bBuf, list<vector<QImage> >* stl_roiBuf, PlayThread* player, QSpinBox* spinBox_ctSize, QImage* s_back = NULL);
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
    void cutShadow(bool shadow_cut);
    void drawMiddle(bool middle_line);

    void setOperat(int operation);
    void setState(int state_t);
    void setAcuracy(int acuracy);
    void setMosaicSize(int mosaic_size);
    void setSigma(double gau_sigma);
    void setEdgeThd(int edge_thd);
    void setShadowCut(double shadow_cut_value);

    int  state();

    virtual void run();
private:
    bool in_privacy_mode;
    bool pain_blob;
    bool with_shape;
    bool shadow_cut;
    bool middle_line;
    // used for opencv shadow_detection
    bool shadow_detect;
    int  pixel_operation;
    int  state_t;
    int  edge_thd;
    int  poly_acuracy;
    int  mosaic_size;
    double gau_sigma;
    double shadow_cut_value;
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
    std::list<vector<QImage> >* roiBuffer;
#endif

    VideoCapture cap;
    BackgroundSubtractorMOG2 bg;

    Blober blober;
    PlayThread* player;

    vector<Point>* middleLine(const Mat& fore, int cut);
    void drawMiddleLine(const Mat& fore, Mat& frame, bool geo_mLine = false, Scalar color = CL_ORANGE, int thickness = 2, int cut = 0);
    void drawMiddleLine(const Mat& fore, vector<Mat> frame, int cut = 0, bool geo_mLine = false, Scalar color = CL_ORANGE, int thickness = 2);
    int greyShadowCut(const Mat& fore, Mat& frame, double thresh);
    int rgbShadowCut(const Mat& fore, Mat& frame, double thresh);
    int hsvShadowCut(const Mat& fore, Mat& frame, double thresh);
    int hsvShadowCut(const Mat& roi_fore, Mat& roi, Mat roi_bg, double alpha, double beta, int tau_s, int tau_h);
    int drawShadowCut(const Mat& fore, Mat& frame, Mat& result, double thresh, Scalar color = CL_GREY, int thickness = 2);
    int drawShadowCut(const Mat& fore, Mat& frame, vector<Mat> result, double thresh, Scalar color = CL_GREY, int thickness = 2);
    void drawShadowCut(const Mat& fore, Mat& frame, Mat& bg_frame, vector<Mat> result, double thresh, Scalar color = CL_GREY, int thickness = 2);
    void drawCutLine(int cut_line, Mat& frame, Scalar color = CL_GREY, int thickness = 2);
    void drawVectorLine(vector<Point> points, Mat& frame, Scalar color = CL_RED, int thickness = 2);
    void drawVectorLine(vector<Point> points, vector<Mat> frames, Scalar color = CL_RED, int thickness = 2);

    Mat cutROI(const Mat frame, const Rect roi, int width = 281, int height = 211);
    void addROIs(const Mat frame, int width = 281, int height = 211);

    void hog(const Mat& frame);
    bool scalarLarger (Scalar sc1, Scalar sc2);
    Scalar maxElement(const Mat& mat);

signals:
    
public slots:
    
};

#endif // FRAMEMANAGER_H
