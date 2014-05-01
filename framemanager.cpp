#include "framemanager.h"
#include "package_bgs/lb/LBMixtureOfGaussians.h"

FrameManager::FrameManager(QObject *parent) :
    QThread(parent)
{
    interval.tv_sec     = 0;
    interval.tv_nsec    = 100000000L; //1 000 000 000nsec = 1sec
    buffered_frame_idx  = 0;
    in_privacy_mode     = false;
    pain_blob           = true;
    shadow_detect       = false;
    with_shape          = false;
    shadow_cut          = false;
    middle_line         = false;
    //pixel_operation     = OP_DEFAULT;
    poly_acuracy        = 1;
    edge_thd            = 15;
    shadow_cut_value    = 3;

    state_t             = ST_PROC;
    timer               = NULL;

    bg.set("nmixtures", 3);
    bg.set("history", HISTORY);
//    bg.bShadowDetection = true;
    bg.set("detectShadows", true);
    static_background   = NULL;
    imgBuffer           = NULL;
    gryBuffer           = NULL;
    dbgBuffer           = NULL;
    backBuffer          = NULL;

    player              = NULL;
    spinBox_ctSize      = NULL;
}
#ifdef STL_LIST
FrameManager::FrameManager(VideoCapture cap, list<QImage>* stl_iBuf, list<QImage>* stl_cBuf, list<QImage>* stl_gBuf, list<QImage>* stl_dBuf, list<QImage>* stl_bBuf, list<vector<QImage> >* stl_roiBuf, PlayThread* player, QSpinBox* spinBox_ctSize, QImage* s_back){
        interval.tv_sec     = 0;
        interval.tv_nsec    = 100000000L; //1 000 000 000nsec = 1sec
//        buffered_frame_idx  = 0;
        in_privacy_mode     = false;
        pain_blob           = true;
        shadow_detect       = false;
        with_shape          = false;
        shadow_cut          = false;
        middle_line         = false;
        //pixel_operation     = OP_DEFAULT;
        poly_acuracy        = 1;
        mosaic_size         = 10;
        gau_sigma           = 2.5;
        edge_thd            = 15;
        shadow_cut_value    = 3;

        state_t             = ST_PROC;
//        timer               = new QTimer(0);
//        connect(timer_ptr, SIGNAL(timeout()), this, SLOT(imageUpdate()));

        bg.set("nmixtures", 3);
        bg.set("history", HISTORY);
        bg.set("detectShadows", true);

        this->cap = cap;
        static_background   = s_back;
        imgBuffer           = stl_iBuf;
        clrBuffer           = stl_cBuf;
        gryBuffer           = stl_gBuf;
        dbgBuffer           = stl_dBuf;
        backBuffer          = stl_bBuf;
        roiBuffer           = stl_roiBuf;

        this->player= player;
        this->spinBox_ctSize = spinBox_ctSize;
}
#endif
FrameManager::~FrameManager(){
    terminate();

    player->stop_play();
    if(timer != NULL)
        delete timer;
    if(static_background != NULL)
        delete static_background;
    imgBuffer->clear();
    gryBuffer->clear();
    dbgBuffer->clear();
    backBuffer->clear();

}

void FrameManager::inPrivacy(bool privacy_mode){
    in_privacy_mode = privacy_mode;
}

void FrameManager::pain_rect(bool paint_blob){
    this->pain_blob = paint_blob;
}

void FrameManager::shadow(bool shadow_detec){
    this->shadow_detect = shadow_detec;
}

void FrameManager::setOperat(int operation){
    pixel_operation = operation;
}

void FrameManager::setShape(bool with_shape){
    this->with_shape = with_shape;
}

void FrameManager::setState(int state_t){
    this->state_t = state_t;
}

void FrameManager::setAcuracy(int acuracy){
    this->poly_acuracy = acuracy;
}

void FrameManager::setMosaicSize(int mosaic_size){
    this->mosaic_size = mosaic_size;
}

void FrameManager::setSigma(double gau_sigma){
    this->gau_sigma = gau_sigma;
}

void FrameManager::setEdgeThd(int edge_thd){
    if(edge_thd >= 0 && edge_thd <= 255)
        this->edge_thd = edge_thd;
}

void FrameManager::setShadowCut(double shadow_cut_value){
    this->shadow_cut_value = shadow_cut_value;
}

void FrameManager::cutShadow(bool shadow_cut){
    this->shadow_cut = shadow_cut;
}

void FrameManager::drawMiddle(bool middle_line){
    this->middle_line = middle_line;
}

int FrameManager::state(){
   return this->state_t;
}

#ifdef STL_LIST
void FrameManager::process(){
#ifdef MESSAGE_ON
    cout << "start to process" << endl;
    cout << "@fmanager.process(): " << currentThreadId() << endl;
#endif
//        fps     = cap.get(CV_CAP_PROP_FPS);
//        width   = cap.get(CV_CAP_PROP_FRAME_WIDTH);
//        height  = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

        Mat frame, frame_gau, back, fore;
        Mat drawing, grey, grey_back, st_back, st_back_grey;
        QImage image, clr_image, grey_image, fore_ground, back_ground;
        LBMixtureOfGaussians* bgs = new LBMixtureOfGaussians;

        for(unsigned int i = 0;; i++) {
            cap >> frame;
            cvtColor(frame, grey, CV_RGB2GRAY);
            cvtColor(grey, grey, CV_GRAY2BGR);
            image = Mat2QImage(frame);


            GaussianBlur(frame, frame_gau, Size(5, 5), 1.5, 1.5);

            /*** subtracting backgrounds from frame using different algorithms ***/
            //bg.operator ()(frame, fore, 0.01);
            //bg.getBackgroundImage(back);
            bgs->process(frame_gau, fore, back);

            //erode(fore, fore, cv::Mat());
            //dilate(fore, fore, cv::Mat());
            cvtColor(back, grey_back, CV_RGB2GRAY);
            cvtColor(grey_back, grey_back, CV_GRAY2BGR);

            /*** in case using the LBMixtureOfGaussianDetector ***/
            cvtColor(fore, fore, CV_RGB2GRAY);
            cvtColor(fore, drawing, CV_GRAY2BGR);
            //cvtColor(fore, drawing, CV_RGB2BGR);
            blober.find_blobs(fore, spinBox_ctSize->value(), shadow_detect, poly_acuracy);

            int cut_line = 0;
            if(shadow_cut == true){
                for(unsigned int i = 0; i < blober.rects()->size(); i++){
                    Rect rec    = blober.rects()->at(i);
                    if(rec.width <= 0 || rec.height <= 0)
                        continue;

                    Mat mask = fore(rec);
                    Mat rat = back(rec);//GaussianBlur(rat, rat, Size(9, 9), gau_sigma, gau_sigma);
                    Mat roi     = frame(rec);
                    Mat roi_c   = grey(rec);
                    vector<Mat> vecs;
                    vecs.push_back(mask);
                    vecs.push_back(roi);
                    vecs.push_back(roi_c);
                    drawShadowCut(mask, roi, rat, vecs, shadow_cut_value, CL_MEGENTA);
                }
            }

            //addROIs(frame);
            if(static_background != NULL){
                st_back = QImage2Mat(*static_background);
                cvtColor(st_back, st_back_grey, CV_RGB2GRAY);
                cvtColor(st_back_grey, st_back_grey, CV_GRAY2BGR);
            } else {
                st_back = back;
                st_back_grey = grey_back;
            }
            /*** add the pixel operation on range of interest ***/
            if(in_privacy_mode == true){
                switch (pixel_operation){
                case OP_BLACK:
                    black_out(st_back, st_back_grey);
                    break;
                case OP_BLUR:
                    blur(frame, drawing, grey, st_back, st_back_grey);
                    break;
                case OP_EDGE:
                    edge(frame, grey, back, grey_back, st_back, st_back_grey);
                    break;
                case OP_BORDER:
                    border(drawing, back, grey_back, st_back, st_back_grey);
                    break;
                case OP_POLY:
                    poly(st_back, st_back_grey);
                    break;
                case OP_MOSAIC:
                    mosaic(frame, grey, st_back, st_back_grey);
                    break;
                default:
                    break;
                }
            }

#ifdef BLOB_ON
            if(pain_blob == true){
                blober.paint_blobs(back, PT_RECT, CL_GREEN);
                blober.paint_blobs(drawing, PT_RECT, CL_GREEN);
                blober.paint_blobs(st_back, PT_RECT, CL_GREEN);
                blober.paint_blobs(st_back_grey, PT_RECT, CL_GREEN);
            }
#endif

{
//                cv::findContours(fore, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//                bigcons.clear();
//                for(int i = 0; i < contours.size(); i++){
//                    if(contours.at(i).size() > 200) {
//                        bigcons.push_back(contours.at(i));
//                    }
//                }
//                cv::drawContours(frame, bigcons, -1, cv::Scalar(0, 255, 0), 2);
//                QImage grey_image(fore.data, frame.cols, frame.rows, QImage::Format_Indexed8);
}
            fore_ground = Mat2QImage(drawing);
            blober.paint_label(&fore_ground);
            back_ground = Mat2QImage(back);
            clr_image   = Mat2QImage(st_back);
            grey_image  = Mat2QImage(st_back_grey);
#ifdef LABEL_ON
            if(pain_blob == true){
                blober.paint_label(&back_ground);
                blober.paint_label(&clr_image);
                blober.paint_label(&grey_image);
            }
#endif
            player->mutex.lock();
            try{
                imgBuffer->push_back(image);
                clrBuffer->push_back(clr_image);
                gryBuffer->push_back(grey_image);
                dbgBuffer->push_back(fore_ground);
                backBuffer->push_back(back_ground);
                //addROIs(frame);
                buffered_frame_idx++;
                player->mutex.unlock();
            } catch(std::bad_alloc& balc){
                cerr << i << ": bad allocation caught at " << buffered_frame_idx << "th frame." << endl;
                player->mutex.unlock();
                //continue;
            }
#ifdef MESSAGE_ON
            cout << "<" << buffered_frame_idx << "> " << "processing @fmanager.run(): " << currentThreadId() << endl;
#endif
            if(state_t == ST_PROC){
                if(player->state() == BUFFERING && imgBuffer->size()-player->get_frame_ctr() > player->get_fps()*2)
                    player->start();
                interval.tv_nsec = 1000000000 / (3*player->get_fps());
                nanosleep(&interval, NULL);
            }
            else
                sleep(3);
        }
}
#endif

void FrameManager::black_out(Mat& st_back, Mat& st_back_grey){
    for(unsigned int i = 0; i <blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        if(rec.width <= 0 || rec.height <= 0)
            continue;
        Mat roi = st_back(rec);
        roi = Mat::zeros(rec.height, rec.width, roi.type());
        roi = st_back_grey(rec);
        roi = Mat::zeros(rec.height, rec.width, roi.type());
    }
}

void FrameManager::blur(Mat &mat, const Mat& fore, Mat& grey, Mat& st_back, Mat& st_back_grey){

    for(unsigned int i = 0; i < blober.rects()->size(); i++){
        Rect rec    = blober.rects()->at(i);

        if(rec.width <= 0 || rec.height <= 0)
            continue;
        Mat rat; mat(rec).copyTo(rat);//GaussianBlur(rat, rat, Size(9, 9), gau_sigma, gau_sigma);
        Mat roi     = mat(rec);
        Mat roi_c   = grey(rec);
        Mat mask    = fore(rec);
        Mat roi_gau, roi_c_gau, inv_mask;

        GaussianBlur(roi, roi_gau, Size(9, 9), gau_sigma, gau_sigma);
        GaussianBlur(roi_c, roi_c_gau, Size(9, 9), gau_sigma, gau_sigma);
        bitwise_and(roi_gau,mask,roi_gau);
        bitwise_and(roi_c_gau,mask,roi_c_gau);
        bitwise_not(mask, inv_mask);
        bitwise_and(roi,inv_mask,roi);
        bitwise_and(roi_c,inv_mask,roi_c);
        roi += roi_gau;
        roi_c += roi_c_gau;

        int cut_line = 0;
        if(middle_line == true){
            vector<Mat> frames;
            frames.push_back(mask);
            frames.push_back(roi);
            frames.push_back(roi_c);
            drawMiddleLine(mask, frames, cut_line);
        }

        //if(cut_line > 0){
        //    Mat croi = mat(Rect(rec.x, rec.y, rec.width, cut_line));
        //    croi.copyTo(st_back(Rect(rec.x, rec.y, rec.width, cut_line)));
        //} else
        roi.copyTo(st_back(rec));
        roi_c.copyTo(st_back_grey(rec));
    }
    //imshow("debug", fore);
    if(with_shape == true)
        poly(st_back, st_back_grey, CL_CYAN);
}

void FrameManager::poly(Mat &st_back, Mat& st_back_grey, Scalar color){
    blober.paint_blobs(st_back, PT_POLY, color);
    blober.paint_blobs(st_back_grey, PT_POLY, color);
}

void FrameManager::mosaic(Mat &mat, Mat& grey, Mat &st_back, Mat& st_back_grey){
    Scalar mean_val;
    for(unsigned int i = 0; i < blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        if(rec.width <= 0 || rec.height <= 0)
            continue;
        Mat roi     = mat(rec);
        Mat groi    = grey(rec);
        cvtColor(groi, groi, CV_BGR2GRAY);
        int m = 0;
        for(m; m < roi.rows - mosaic_size; m+=mosaic_size){
            int n = 0;
            for(n; n < roi.cols - mosaic_size; n+=mosaic_size){
                Mat gblock = groi(Rect(n, m, mosaic_size, mosaic_size));
                mean_val = mean(gblock);
                gblock = Mat::ones(mosaic_size, mosaic_size, gblock.type())*(unsigned char)mean_val[0];

                Mat block = roi(Rect(n, m, mosaic_size,mosaic_size));
                mean_val = mean(block);
                cv::Mat(mosaic_size, mosaic_size, block.type(), Scalar(mean_val[0], mean_val[1], mean_val[2])).copyTo(block);
            }
            Mat gblock = groi(Rect(n, m, groi.cols-n, mosaic_size));
            mean_val = mean(gblock);
            gblock = Mat::ones(mosaic_size, groi.cols-n, gblock.type())*(unsigned char)mean_val[0];

            Mat block = roi(Rect(n, m, groi.cols-n, mosaic_size));
            mean_val = mean(block);
            cv::Mat(mosaic_size, groi.cols-n, block.type(), Scalar(mean_val[0], mean_val[1], mean_val[2])).copyTo(block);
        }
        int n = 0;
        for(n; n < roi.cols - mosaic_size; n+=mosaic_size){
            Mat gblock = groi(Rect(n, m, mosaic_size, groi.rows-m));
            mean_val = mean(gblock);
            gblock = Mat::ones(groi.rows-m, mosaic_size, gblock.type())*(unsigned char)mean_val[0];

            Mat block = roi(Rect(n, m, mosaic_size, groi.rows-m));
            mean_val = mean(block);
            cv::Mat(groi.rows-m, mosaic_size, block.type(), Scalar(mean_val[0], mean_val[1], mean_val[2])).copyTo(block);
        }
        Mat gblock = groi(Rect(n, m, groi.cols-n, groi.rows-m));
        mean_val = mean(gblock);
        gblock = Mat::ones(groi.rows-m, groi.cols-n, gblock.type())*(unsigned char)mean_val[0];

        Mat block = roi(Rect(n, m, groi.cols-n, groi.rows-m));
        mean_val = mean(block);
        cv::Mat(groi.rows-m, groi.cols-n, block.type(), Scalar(mean_val[0], mean_val[1], mean_val[2])).copyTo(block);

        cvtColor(groi, groi, CV_GRAY2BGR);
        roi.copyTo(st_back(rec));
        groi.copyTo(st_back_grey(rec));
    }
    if(with_shape == true)
        poly(st_back, st_back_grey, CL_CYAN);
}

void FrameManager::edge(Mat &mat, Mat& grey, const Mat& back, const Mat& grey_back, Mat& st_back, Mat& st_back_grey){
    Mat sobel_x, sobel_y, sobel;
    for(unsigned int i = 0; i < blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        if(rec.width <= 0 || rec.height <= 0)
            continue;
        Mat roi = grey(rec);
        GaussianBlur(roi, roi, Size(7, 7), 1.5, 1.5);
        Sobel(roi, sobel_x, -1, 0, 1);
        Sobel(roi, sobel_y, -1, 1, 0);
        sobel = sobel_x + sobel_y;
        threshold(sobel, sobel, edge_thd, 255, THRESH_TOZERO);
        st_back(rec) = sobel + back(rec);
        st_back_grey(rec) = sobel + grey_back(rec);
    }
    if(with_shape)
        poly(st_back, st_back_grey, CL_CYAN);
}

void FrameManager::border(const Mat& fore, const Mat& back, const Mat& grey_back, Mat& st_back, Mat& st_back_grey){
    Mat sobel_x, sobel_y, sobel;
    for(unsigned int i = 0; i <blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        if(rec.width <= 0 || rec.height <= 0)
            continue;

        Sobel(fore(rec), sobel_x, -1, 0, 1);
        Sobel(fore(rec), sobel_y, -1, 1, 0);
        st_back(rec) = sobel_x+sobel_y+back(rec);
        st_back_grey(rec) = sobel_x+sobel_y+grey_back(rec);
    }
}

Mat FrameManager::cutROI(const Mat frame, const Rect roi, int width, int height){
    //width = roi.width > width ? roi.width : width;
    height = roi.height > height ? roi.height : height;
    int z_x = roi.x + roi.width/2;
    int z_y = roi.y + roi.height/2;
    if(z_x - width/2 < 0){
        //width = width/2 + z_x;
        z_x = 0;
    } else if(z_x + width/2 >= frame.cols){
        z_x = frame.cols-1 - width;
    } else {
        z_x -= width/2;
    }

    if(z_y - height/2 < 0){
        //height = height/2 + z_y;
        z_y = 0;
    } else if(z_y + height/2 >= frame.rows){
        z_y = frame.rows-1 - height;
    } else {
        z_y -= height/2;
    }
    Mat cut;
    frame(Rect(z_x, z_y, width, height)).copyTo(cut);
    return cut;
}

void FrameManager::addROIs(const Mat frame, int width, int height){
    vector<QImage> vec;// = new vector<QImage>();
    for(unsigned int i = 0; i < blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        if(rec.width <= 0 || rec.height <= 0)
            continue;

        Mat roi = cutROI(frame, rec, width, height);
        QImage roi_image = Mat2QImage(roi);
        vec.push_back(roi_image);
    }
    roiBuffer->push_back(vec);
}

/*
void FrameManager::virtualCams(const Mat frame, int x, int y, int width, int height){
    vector<QImage> vec;// = new vector<QImage>();
    for(unsigned int i = 0; i < blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        if(rec.width <= 0 || rec.height <= 0)
            continue;

        Mat roi = cutROI(frame, rec, width, height);
        QImage roi_image = Mat2QImage(roi);
        vec.push_back(roi_image);
    }
    roiBuffer->push_back(vec);
}*/

cv::Mat FrameManager::QImage2Mat(QImage const& src)
{
    QImage cvt;
    if(src.format() != QImage::Format_RGB888)
        cvt = src.convertToFormat(QImage::Format_RGB888);
    else
        cvt = src;
    cv::Mat tmp(cvt.height(),cvt.width(),CV_8UC3,(uchar*)cvt.bits(), cvt.bytesPerLine());
    cv::Mat result;
    cvtColor(tmp, result,CV_RGB2BGR);

    return result;
}

QImage FrameManager::Mat2QImage(cv::Mat const& src)
{
    cv::Mat temp; // make the same cv::Mat
    QImage::Format format;
    if(src.channels() == 3){
     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
     format = QImage::Format_RGB888;
    } else {
        temp = src;
        format = QImage::Format_Indexed8;
    }
    QImage dest((uchar*) temp.data, temp.cols, temp.rows, temp.step, format);
    QImage dest2(dest);
    dest2.detach(); // enforce deep copy
    return dest2;
}

void FrameManager::run(){
#ifdef MESSAGE_ON
    cout << "@fmanager.run(): " << currentThreadId() << endl;
#endif
    process();
}

void FrameManager::gamma_correction(Mat &mat, const double gamma){
    mat = mat * gamma;
}

unsigned int FrameManager::buffered_frame(){
    return buffered_frame_idx;
}

vector<Point>* FrameManager::middleLine(const Mat &fore, int cut){
    Mat fore_c1;
    if(fore.channels() == 3)
        cvtColor(fore,fore_c1, CV_BGR2GRAY);

    if(cut <= 0)
        cut = fore_c1.rows - 5;

    vector<Point>* middle_dots = new vector<Point>();
    for(int i = 5; i < cut; i+=5){
        int begin = 0; int end = 0;
        for(int n = 0; n < fore_c1.cols; n++){
            if(fore_c1.at<uchar>(i,n) != 0 && begin == 0){
                end = n;
                begin = n;
            } else
                end = fore_c1.at<uchar>(i,n) != 0 ? end+1 : end;
        }
        middle_dots->push_back(Point(begin+(end-begin)/2, i));
    }
    return middle_dots;
}

void FrameManager::drawMiddleLine(const Mat &fore, Mat &frame, bool geo_mLine, Scalar color, int thickness, int cut){
    vector<Point>* middle_dots = middleLine(fore, cut);
    if(!middle_dots->empty())
        drawVectorLine(*middle_dots, frame, color, thickness);

    if(geo_mLine == true)
        line(frame, Point(frame.cols/2, 0), Point(frame.cols/2, frame.rows-1), CL_YELLOW, 2);
}

void FrameManager::drawMiddleLine(const Mat &fore, vector<Mat> frame, int cut, bool geo_mLine, Scalar color, int thickness){
    vector<Point>* middle_dots = middleLine(fore, cut);
    if(!middle_dots->empty()){
        for(vector<Mat>::iterator itr= frame.begin(); itr != frame.end(); itr++){
            drawVectorLine(*middle_dots, *itr, color, thickness);
            if(geo_mLine == true)
                line(*itr, Point((*itr).cols/2, 0), Point((*itr).cols/2, (*itr).rows-1), CL_YELLOW, 2);
        }
    }
}

void FrameManager::drawVectorLine(vector<Point> points, Mat& frame, Scalar color, int thickness){
    while(points.size() >= 2){
        Point p1, p2;
        p1 = points.back();
        points.pop_back();
        p2 = points.back();
        points.pop_back();
        line(frame, p2, p1, color, thickness);
    }
}

void FrameManager::drawVectorLine(vector<Point> points, vector<Mat> frames, Scalar color, int thickness){
    for(vector<Mat>::iterator fitr = frames.begin(); fitr != frames.end(); fitr++){
        while(points.size() >= 2){
            Point p1, p2;
            p1 = points.back();
            points.pop_back();
            p2 = points.back();
            points.pop_back();
            line(*fitr, p2, p1, color, thickness);
        }
    }
}

void FrameManager::drawShadowCut(const Mat &fore, Mat &frame, Mat &bg_frame, vector<Mat> result, double thresh, Scalar color, int thickness){
    //int cut_line = rgbShadowCut(fore, frame, 3);
    int sut_line = hsvShadowCut(fore, frame, bg_frame,  0, 4.0, 20, 30);
    //for(vector<Mat>::iterator itr = result.begin(); cut_line >= 0 && itr != result.end(); itr++){
        //cv::line(*itr, Point(0, cut_line), Point(fore.cols-1, cut_line), color, thickness);
        //cv::line(*itr, Point(0, sut_line), Point(fore.cols-1, sut_line), CL_CYAN, thickness);
    //}
}

//todo: finish.
// use estimatet the shadow cut in hsv mode.
int FrameManager::hsvShadowCut(const Mat &fore, Mat &frame, double thresh){
    Mat fore_c1;
    if(fore.channels() == 3)
        cvtColor(fore,fore_c1, CV_BGR2GRAY);

    int height = 1;
    Scalar mValue, mStd, cValue, cStd;
    for(int i = fore.rows-height; i > fore.rows/2; i--){
        Mat line = frame(Rect(0, i, fore.cols, height));
        Mat cut_line = frame(Rect(0, i-height, fore.cols, height));
        Mat mask = fore_c1(Rect(0, i, fore.cols, height));
        Mat inv_mask, cut;
        bitwise_not(mask, inv_mask);

        cvtColor(line, line, CV_BGR2HSV);
        cvtColor(cut_line, cut_line, CV_BGR2HSV);
        meanStdDev(line, mValue, mStd, mask);
        meanStdDev(cut_line, cValue, cStd, mask);

        absdiff(mValue, cValue, mValue);
        absdiff(mStd, cStd, mStd);
        if(mStd[1] > thresh){
            return i;
        }
    }
    return -1;
}

int FrameManager::hsvShadowCut(const Mat& roi_fore, Mat& roi, Mat roi_bg, double alpha, double beta, int tau_s, int tau_h){

    Mat roi_hsv, bg_hsv, fore_cut;
    GaussianBlur(roi_bg, roi_bg, Size(5,5), 1.5, 1.5);
    cvtColor(roi, roi_hsv, CV_BGR2HSV);
    cvtColor(roi_bg, bg_hsv, CV_BGR2HSV);
    //roi_fore.copyTo(fore_cut);
    Scalar mValue, cValue;
    for(int i = 0; i < roi.rows; i++){
        for(int j = 0; j < roi.cols; j++){
            Vec3b r_p = roi_hsv.at<Vec3b>(i,j);
            Vec3b b_p = bg_hsv.at<Vec3b>(i,j);
            int d_s = roi_hsv.at<Vec3b>(i,j).val[1] - bg_hsv.at<Vec3b>(i,j).val[1];
            int d_h = roi_hsv.at<Vec3b>(i,j).val[0] - bg_hsv.at<Vec3b>(i,j).val[0];
            double r_v = roi_hsv.at<Vec3b>(i,j).val[2] / (bg_hsv.at<Vec3b>(i,j).val[2]+1);
            d_h = d_h > 0 ? d_h : 0 - d_h;
            if(( d_s< tau_s) &&
                (d_h < tau_h) &&
                (r_v <= beta && r_v >= alpha)){
                roi.at<Vec3b>(i,j).val[0] = 0;
                roi.at<Vec3b>(i,j).val[1] = 0;
                roi.at<Vec3b>(i,j).val[2] = 0;
            }
        }
    }
    return -1;
}

//todo: finish.
int FrameManager::greyShadowCut(const Mat &fore, Mat &frame, double thresh){
    Mat fore_c1, frame_c1, sobel_x, sobel_y;
    if(fore.channels() == 3)
        cvtColor(fore,fore_c1, CV_BGR2GRAY);
    if(frame.channels() == 3)
        cvtColor(frame, frame_c1, CV_BGR2GRAY);
    Sobel(frame_c1, sobel_x, -1, 0, 1);
    Sobel(frame_c1, sobel_y, -1, 1, 0);
    frame_c1 = sobel_x + sobel_y;
    //GaussianBlur(frame_c1, frame_c1, Size(3, 3), 1.5, 1.5);
    //threshold(frame_c1, frame_c1, 25, 255, cv::THRESH_BINARY);

    int height = 1;
    Scalar mValue, mStdv, cValue, cStdv;
    for(int i = fore.rows-height; i > fore.rows/3; i--){
        Mat line = frame_c1(Rect(0, i, fore.cols, height));
        //Mat mask = fore_c1(Rect(0, i, fore.cols, height));
        meanStdDev(line, mValue, mStdv);

        Mat cut_line = frame_c1(Rect(0, i-height, fore.cols, height));
        //Mat cut_mask = fore_c1(Rect(0, i-height, fore.cols, height));
        //meanStdDev(cut_line, cValue, cStdv, cut_mask);

        //absdiff(mStdv, cStdv, mStdv);
        if(mStdv[0]>5){
            //cout << "dev" << mStdv << endl;
            imshow("frame_debug", frame_c1);
            imshow("cut_debug", frame_c1(Rect(0, 0, fore.cols, i)));
            return i;
        }
    }
    return -1;
}

int FrameManager::rgbShadowCut(const Mat &fore, Mat &frame, double thresh){
    Mat fore_c1;
    if(fore.channels() == 3)
        cvtColor(fore,fore_c1, CV_BGR2GRAY);

    int height = 1;
    Scalar mValue, mStdv, cValue, cStdv;
    for(int i = fore.rows-height; i > fore.rows/2; i--){
        Mat line = frame(Rect(0, i, fore.cols, height));
        Mat mask = fore_c1(Rect(0, i, fore.cols, height));
        meanStdDev(line, mValue, mStdv, mask);

        Mat cut = frame(Rect(0, i-height, fore.cols, height));
        Mat cut_mask = fore_c1(Rect(0, i-height, fore.cols, height));
        meanStdDev(cut, cValue, cStdv, cut_mask);
        absdiff(mValue, cValue, mValue);
        //absdiff(mStdv, cStdv, mStdv);
        if(mValue[0]>thresh && mValue[1]>thresh && mValue[2]>thresh){
            //cout << "dev" << mStdv << endl;
            return i;
        }
    }
    return -1;
}

int FrameManager::drawShadowCut(const Mat &fore, Mat &frame, Mat& result, double thresh, Scalar color, int thickness){
    //int cut = rgbShadowCut(fore, frame, thresh);
    int cut = hsvShadowCut(fore, frame, result, 0.3, 1.0, 20, 20);
    if(cut >= 0)
        //cv::line(result, Point(0, cut), Point(fore.cols-1, cut), color, thickness);
        cv::line(result, Point(0, cut), Point(fore.cols-1, cut), CL_CYAN, thickness);
    return cut;
}

int FrameManager::drawShadowCut(const Mat &fore, Mat &frame, vector<Mat> result, double thresh, Scalar color, int thickness){
    int cut_line = rgbShadowCut(fore, frame, thresh);
    for(vector<Mat>::iterator itr = result.begin(); cut_line >= 0 && itr != result.end(); itr++){
        cv::line(*itr, Point(0, cut_line), Point(fore.cols-1, cut_line), color, thickness);
    }
    return cut_line;
}

void FrameManager::drawCutLine(int cut_line, Mat &frame, Scalar color, int thickness){
    if(cut_line >= 0 && cut_line <= frame.rows-1)
        cv::line(frame, Point(0, cut_line), Point(frame.cols-1, cut_line), color, thickness);
}

void FrameManager::hog(const Mat &frame){
    HOGDescriptor hog;
    vector<float> ders;
    vector<Point> locs;

    hog.compute(frame, ders, Size(32, 32), Size(0,0), locs);


}

bool FrameManager::scalarLarger(Scalar sc1, Scalar sc2){

    return (sc1[0] >= sc2[0] && sc1[1] >= sc2[1] && sc1[2] >= sc2[2] && sc1[3] >= sc2[3]) ? true : false;
}

Scalar FrameManager::maxElement(const Mat &mat){
    Scalar max = Scalar(0, 0, 0);
    for(int i = 0; i < mat.rows; i++){
        for(int j = 0; j < mat.cols; j++){
            max[0] = max[0] < mat.at<uchar>(i,j) ? max[0] : mat.at<uchar>(i,j);
        }
    }
    return max;
}
