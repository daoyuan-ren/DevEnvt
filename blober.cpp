#include "blober.h"

Blober::Blober()
{
    color           = NULL;
    contours_poly   = NULL;
    boundRect       = NULL;
#ifdef CIRCLE
    center          = NULL;
    radius          = NULL;
#endif
    blob_num        = 0;
}

Blober::Blober(int size){
    create(size);
}

void Blober::create(int size){
    blob_num        = size;
    color           = new Scalar(0, 0, 255);
    contours_poly   = new vector< vector<Point> >(size);
    boundRect       = new vector<Rect>(size);
#ifdef CIRCLE
    center          = new vector<Point2f>(size);
    radius          = new vector<float>(size);
#endif
}

int Blober::size(){
    return blob_num;
}

void Blober::find_blobs(Mat &frame, Mat &drawing, int blob_minSize){
    Mat temp;
    frame.copyTo(temp);
    cv::findContours(temp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    create(contours.size());

    for(int i = 0; i < blob_num; i++)
    {
        if(contours[i].size() >= blob_minSize){
            approxPolyDP( Mat(contours[i]), (*contours_poly)[i], 3, true );
            (*boundRect)[i] = boundingRect( Mat((*contours_poly)[i]) );
#ifdef CIRELE
            minEnclosingCircle( (Mat)(*contours_poly)[i], (*center)[i], (*radius)[i] );
#endif
        }
    }

    for( int i = 0; i < boundRect->size(); i++ )
    {
#ifdef POLY
        drawContours( drawing, blobs.contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
#endif
        rectangle(drawing, (*boundRect)[i].tl(), (*boundRect)[i].br(), *color, 2);
#ifdef CIRCLE
        circle(drawing, (*center)[i], (int)(*radius)[i], *color, 2);
#endif
    }
}

void Blober::paint_blobs(QImage* image){
    for(int i = 0; i < blob_num; i++){
        QPainter* painter = new QPainter(image); // sorry i forgot the "&"
        painter->setPen(Qt::white);
        painter->setFont(QFont("Arial", 12));
        string text = drawText((*boundRect)[i].x, (*boundRect)[i].y, (*boundRect)[i].width, (*boundRect)[i].height);
        painter->drawText((*boundRect)[i].x, (*boundRect)[i].y, QString::fromStdString(text));
        delete painter;
    }
}

string Blober::drawText(int x, int y, int width, int height){
    ostringstream ss;
    ss << "(" << x <<", " << y << ")<" << width << ", " << height << ">";
    return ss.str();
}
