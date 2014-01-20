#ifndef BLOB_H
#define BLOB_H
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <QPainter>

using namespace cv;
using namespace std;

#define POLY

#define PT_POLY 10
#define PT_RECT 11
#define PT_CIRC 12

#define CL_RED      Scalar(255, 0, 0)
#define CL_GREEN    Scalar(0, 255, 127)
#define CL_BLUE     Scalar(255, 0, 0)
#define CL_YELLOW   Scalar(0, 255, 255)

class Blober
{
public:
    Blober();
    Blober(int blob_num);

    void create(int blob_num);

    Scalar color;
    vector<vector<Point> >* contours_poly;
    vector<Rect>* boundRect;
    vector< vector<Point> > contours;

#ifdef CIRCLE
    vector<Point2f>* center;
    vector<float>* radius;
#endif
    int size();
    void find_blobs(Mat& frame, int blob_minSize, bool shadow_detect);
    void paint_label(QImage* image);
    void paint_blobs(Mat& drawing);
    void paint_blobs(Mat &drawing, int shape_t);
    string drawText(int x, int y, int width, int height);

    vector<Rect>* rects();
private:
    int blob_num;
};

#endif // BLOB_H
