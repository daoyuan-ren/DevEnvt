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
    //pixel_operation     = OP_DEFAULT;
    poly_acuracy        = 1;
    edge_thd            = 15;

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

FrameManager::FrameManager(VideoCapture cap, list<QImage>* stl_iBuf, list<QImage>* stl_cBuf, list<QImage>* stl_gBuf, list<QImage>* stl_dBuf, list<QImage>* stl_bBuf, PlayThread* player, QSpinBox* spinBox_ctSize, QImage* s_back){
        interval.tv_sec     = 0;
        interval.tv_nsec    = 100000000L; //1 000 000 000nsec = 1sec
        buffered_frame_idx  = 0;
        in_privacy_mode     = false;
        pain_blob           = true;
        shadow_detect       = false;
        with_shape          = false;
        //pixel_operation     = OP_DEFAULT;
        poly_acuracy        = 1;
        mosaic_size         = 10;
        gau_sigma           = 2.5;
        edge_thd            = 15;

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

        this->player= player;
        this->spinBox_ctSize = spinBox_ctSize;
}

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

int FrameManager::state(){
   return this->state_t;
}

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

            if(static_background != NULL){
                st_back = QImage2Mat(*static_background);
                cvtColor(st_back, st_back_grey, CV_RGB2GRAY);
                cvtColor(st_back_grey, st_back_grey, CV_GRAY2BGR);
            }
            else
                st_back = grey_back;
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
        roi.copyTo(st_back(rec));
        roi_c.copyTo(st_back_grey(rec));
    }
    if(with_shape == true)
        poly(st_back, st_back_grey, CL_SKY);
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
        poly(st_back, st_back_grey, CL_SKY);
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
        poly(st_back, st_back_grey, CL_SKY);
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
