#include "blober.h"

Blober::Blober()
{
    contours_poly   = NULL;
    boundRect       = NULL;
    color           = CL_GREEN;
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
    contours_poly   = new vector< vector<Point> >(size);
    boundRect       = new vector<Rect>(size);
    color           = CL_GREEN;
#ifdef CIRCLE
    center          = new vector<Point2f>(size);
    radius          = new vector<float>(size);
#endif
}

int Blober::size(){
    return blob_num;
}

void Blober::cv_shadow_detect(Mat &frame){
    threshold(frame, frame, 128, 255, cv::THRESH_BINARY);
}

void Blober::find_blobs(Mat &frame, int blob_minSize, bool shadow_detect, int epsilon){
    if(frame.empty())
        return;
    Mat temp;
    frame.copyTo(temp);
    if(shadow_detect == true){
        cv_shadow_detect(temp);
    }
    cv::findContours(temp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    create(contours.size());

    for(int i = 0; i < blob_num; i++)
    {
        if(contours[i].size() >= blob_minSize){
            approxPolyDP( Mat(contours[i]), (*contours_poly)[i], epsilon, true );
            (*boundRect)[i] = boundingRect( Mat((*contours_poly)[i]) );
#ifdef CIRELE
            minEnclosingCircle( (Mat)(*contours_poly)[i], (*center)[i], (*radius)[i] );
#endif
        }
    }
    {
        // find the shadow down-top.
        /*    if(shadow_detect == true){
        //        Mat sub;
        //        double min_val, max_val;
        //        for(int i = 0; i < boundRect->size(); i++){
        //            if((*boundRect)[i].width > 0 && (*boundRect)[i].height > 0){
        //                sub = frame((*boundRect)[i]);
        //                int cut = sub.rows-1;
        //                for(; cut > 0 && (unsigned char)max_val < 128; cut--){
        //                    minMaxLoc(sub(Rect(0, cut, sub.cols,1)), &min_val, &max_val);
        //                }
        //                (*boundRect)[i].height = cut+1;
        //            }
        //        }
        //    }
        */
    }
}

void Blober::paint_blobs(Mat &drawing){
    for( int i = 0; i < boundRect->size(); i++ )
    {
#ifdef POLY
        drawContours( drawing, *contours_poly, i, CL_BLUE, 2, 8, vector<Vec4i>(), 0, Point() );
#endif
        rectangle(drawing, (*boundRect)[i].tl(), (*boundRect)[i].br(), color, 2);
#ifdef CIRCLE
        circle(drawing, (*center)[i], (int)(*radius)[i], *color, 2);
#endif
    }
}

void Blober::paint_blobs(Mat &drawing, int shape_t, Scalar color){

    if(contours_poly->empty())
        return;
    for( int i = 0; i < boundRect->size(); i++ )
    {

#ifdef POLY
        if(shape_t == PT_POLY)
            drawContours( drawing, *contours_poly, i, color, 2, 8, vector<Vec4i>(), 0, Point() );
#endif
        if(shape_t == PT_RECT)
            rectangle(drawing, (*boundRect)[i].tl(), (*boundRect)[i].br(), color, 2);
#ifdef CIRCLE
        if(shape_t == PT_CIRC)
            circle(drawing, (*center)[i], (int)(*radius)[i], *color, 2);
#endif
    }
}

void Blober::paint_label(QImage* image){
    if(image->isNull())
        return;
    for(int i = 0; i < blob_num; i++){
        QPainter* painter = new QPainter(image); // sorry i forgot the "&"
        painter->setPen(Qt::red);
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

vector<Rect>* Blober::rects(){
    return boundRect;
}
