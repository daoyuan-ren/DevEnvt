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
    void find_blobs(Mat& frame, int blob_minSize);
    void paint_label(QImage* image);
    void paint_blobs(Mat& drawing);
    string drawText(int x, int y, int width, int height);

    vector<Rect>* rects();
private:
    int blob_num;
};

#endif // BLOB_H
