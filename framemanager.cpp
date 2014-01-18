#include "framemanager.h"

FrameManager::FrameManager(QObject *parent) :
    QThread(parent)
{
    interval.tv_sec     = 0;
    interval.tv_nsec    = 100000000L; //1 000 000 000nsec = 1sec
    buffered_frame_idx  = 0;
    in_privacy_mode     = false;
    pain_blob           = true;
    shadow_detect       = true;
    pixel_operation     = OP_DEFAULT;

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

FrameManager::FrameManager(VideoCapture cap, QList<QImage> *iBuf, QList<QImage>* gBuf, QList<QImage> *dBuf, QList<QImage> *bBuf, PlayThread* player, QSpinBox* spinBox_ctSize, QImage* s_back){
    interval.tv_sec     = 0;
    interval.tv_nsec    = 100000000L; //1 000 000 000nsec = 1sec
    buffered_frame_idx  = 0;
    in_privacy_mode     = false;
    pain_blob           = true;
    shadow_detect       = true;
    pixel_operation     = OP_DEFAULT;

    bg.set("nmixtures", 3);
    bg.set("history", HISTORY);
//    bg.bShadowDetection = true;
    bg.set("detectShadows", true);

    this->cap = cap;
    static_background   = s_back;
    imgBuffer           = iBuf;
    gryBuffer           = gBuf;
    dbgBuffer           = dBuf;
    backBuffer          = bBuf;

    this->player= player;
    this->spinBox_ctSize = spinBox_ctSize;
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

void FrameManager::process(){
#ifdef MESSAGE_ON
    cout << "start to process" << endl;
    cout << "@fmanager.process(): " << currentThreadId() << endl;
#endif
//        fps     = cap.get(CV_CAP_PROP_FPS);
//        width   = cap.get(CV_CAP_PROP_FRAME_WIDTH);
//        height  = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

        Mat frame, back, fore;
        Mat drawing, grey, grey_back, st_back;
        QImage image, grey_image, fore_ground, back_ground;

        for(int i = 0;; i++) {
            cap >> frame;
            cvtColor(frame, grey, CV_RGB2GRAY);
            cvtColor(grey, grey, CV_GRAY2BGR);
            image = Mat2QImage(frame);

            GaussianBlur(frame, frame, Size(7, 7), 1.5, 1.5);
            bg.operator ()(frame, fore, 0.01);
            bg.getBackgroundImage(back);
            erode(fore, fore, cv::Mat());
            dilate(fore, fore, cv::Mat());
            cvtColor(back, grey_back, CV_RGB2GRAY);
            cvtColor(grey_back, grey_back, CV_GRAY2BGR);

            cvtColor(fore, drawing, CV_GRAY2BGR);
            blober.find_blobs(fore, spinBox_ctSize->value(), shadow_detect);

            if(static_background != NULL){
                st_back = QImage2Mat(*static_background);
                cvtColor(st_back, st_back, CV_RGB2GRAY);
                cvtColor(st_back, st_back, CV_GRAY2BGR);
            }
            else
                st_back = grey_back;

            /*** add the pixel operation on range of interest ***/
            if(in_privacy_mode == true){
                switch (pixel_operation){
                case OP_BLACK:
                    black_out(st_back);
                    break;
                case OP_BLUR:
                    blur(grey, st_back);
                    break;
                case OP_EDGE:
                    edge(grey, grey_back, st_back);
                    break;
                case OP_BORDER:
                    border(grey, drawing, grey_back, st_back);
                    break;
                case OP_MOSAIC:
                    mosaic(grey, st_back);
                    break;
                default:
                    break;
                }
            }
            blober.paint_blobs(drawing);
#ifdef BLOB_ON
            if(pain_blob == true){
                blober.paint_blobs(back);
//                blober.paint_blobs(grey);
                blober.paint_blobs(st_back);
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
//            grey_image  = Mat2QImage(grey);
            grey_image  = Mat2QImage(st_back);
//            grey_image = *static_background;
#ifdef LABEL_ON
            if(pain_blob == true){
                blober.paint_label(&back_ground);
                blober.paint_label(&grey_image);
            }
#endif
            player->mutex.lock();
            imgBuffer->append(image);
            gryBuffer->append(grey_image);
            dbgBuffer->append(fore_ground);
            backBuffer->append(back_ground);
            buffered_frame_idx++;
            player->mutex.unlock();

#ifdef MESSAGE_ON
            cout << "<" << buffered_frame_idx << "> " << "processing @fmanager.run(): " << currentThreadId() << endl;
#endif
            nanosleep(&interval, NULL);
        }
}

void FrameManager::black_out(Mat& st_back){
    for(unsigned int i = 0; i <blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        if(rec.width <= 0 || rec.height <= 0)
            continue;
        Mat roi = st_back(rec);
        roi = Mat::zeros(rec.height, rec.width, roi.type());
    }
}

void FrameManager::blur(Mat &mat, Mat& st_back){
    for(unsigned int i = 0; i < blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        if(rec.width <= 0 || rec.height <= 0)
            continue;
        Mat roi = mat(rec);
        GaussianBlur(roi, roi, Size(9, 9), 2.5, 2.5);
        roi.copyTo(st_back(rec));
    }
}

void FrameManager::mosaic(Mat &mat, Mat &st_back){
    int dist = 10;
    Scalar mean_val;
    for(unsigned int i = 0; i < blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        if(rec.width <= 0 || rec.height <= 0)
            continue;
        Mat roi = mat(rec);
        cvtColor(roi, roi, CV_BGR2GRAY);
        int m = 0;
        for(m; m < roi.rows - dist; m+=dist){
            int n = 0;
            for(n; n < roi.cols - dist; n+=dist){
                Mat block = roi(Rect(n, m, dist,dist));
                mean_val = mean(block);
                block = Mat::ones(dist, dist, block.type())*(unsigned char)mean_val[0];
            }
            Mat block = roi(Rect(n, m, roi.cols-n,dist));
            mean_val = mean(block);
            block = Mat::ones(dist, roi.cols-n, block.type())*(unsigned char)mean_val[0];
        }
        int n = 0;
        for(n; n < roi.cols - dist; n+=dist){
            Mat block = roi(Rect(n, m, dist, roi.rows-m));
            mean_val = mean(block);
            block = Mat::ones(roi.rows-m, dist, block.type())*(unsigned char)mean_val[0];
        }
        Mat block = roi(Rect(n, m, roi.cols-n,roi.rows-m));
        mean_val = mean(block);
        block = Mat::ones(roi.rows-m, roi.cols-n, block.type())*(unsigned char)mean_val[0];

        cvtColor(roi, roi, CV_GRAY2BGR);
        roi.copyTo(st_back(rec));
    }
}

void FrameManager::edge(Mat &mat, const Mat& back, Mat& st_back){
    Mat sobel_x, sobel_y, sobel;
    for(unsigned int i = 0; i < blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        if(rec.width <= 0 || rec.height <= 0)
            continue;
        Mat roi = mat(rec);
        GaussianBlur(roi, roi, Size(7, 7), 1.5, 1.5);
        Sobel(roi, sobel_x, -1, 0, 1);
        Sobel(roi, sobel_y, -1, 1, 0);
        st_back(rec) = sobel_x+sobel_y+back(rec);
    }
}

void FrameManager::border(Mat &mat, const Mat& fore, const Mat& back, Mat& st_back){
    Mat sobel_x, sobel_y, sobel;
    for(unsigned int i = 0; i <blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        if(rec.width <= 0 || rec.height <= 0)
            continue;

        Sobel(fore(rec), sobel_x, -1, 0, 1);
        Sobel(fore(rec), sobel_y, -1, 1, 0);
        st_back(rec) = sobel_x+sobel_y+back(rec);
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
