#include "framemanager.h"

FrameManager::FrameManager(QObject *parent) :
    QThread(parent)
{
    interval.tv_sec     = 0;
    interval.tv_nsec    = 100000000L; //1 000 000 000nsec = 1sec
    buffered_frame_idx  = 0;

    bg.set("nmixtures", 3);
    bg.set("history", 108);
//    bg.bShadowDetection = true;
    bg.set("detectShadows", true);
    imgBuffer       = NULL;
    gryBuffer       = NULL;
    dbgBuffer       = NULL;
    backBuffer      = NULL;

    player          = NULL;
    spinBox_ctSize  = NULL;
}

FrameManager::FrameManager(VideoCapture cap, QList<QImage> *iBuf, QList<QImage>* gBuf, QList<QImage> *dBuf, QList<QImage> *bBuf, PlayThread* player, QSpinBox* spinBox_ctSize){
    interval.tv_sec     = 0;
    interval.tv_nsec    = 200000000L; //1 000 000 000nsec = 1sec
    buffered_frame_idx  = 0;

    bg.set("nmixtures", 3);
    bg.set("history", 108);
//    bg.bShadowDetection = true;
    bg.set("detectShadows", true);

    this->cap = cap;
    imgBuffer   = iBuf;
    gryBuffer   = gBuf;
    dbgBuffer   = dBuf;
    backBuffer  = bBuf;

    this->player= player;
    this->spinBox_ctSize = spinBox_ctSize;
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
        Mat drawing, grey, grey_back;
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
            blober.find_blobs(fore, spinBox_ctSize->value());

            /*** add the pixel operation on range of interest ***/
//            black_out(grey);

//            blur(grey);

            edge(grey, grey_back);

            blober.paint_blobs(drawing);
#ifdef BLOB_ON
            blober.paint_blobs(back);
            blober.paint_blobs(grey);
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
            grey_image  = Mat2QImage(grey);
#ifdef BLOB_ON
            blober.paint_label(&back_ground);
            blober.paint_label(&grey_image);
#endif
            player->mutex.lock();
            imgBuffer->append(image);
            gryBuffer->append(grey_image);
            dbgBuffer->append(fore_ground);
            backBuffer->append(back_ground);
            buffered_frame_idx++;
            player->mutex.unlock();

//            imshow("back", back);
//            imshow("drawing", drawing);
//            imshow("frame", frame);
//            cout << "fore: " << i << endl;
#ifdef MESSAGE_ON
            cout << "<" << buffered_frame_idx << "> " << "processing @fmanager.run(): " << currentThreadId() << endl;
#endif
            nanosleep(&interval, NULL);
//            if(waitKey(30) >= 0){
//                player->stop_play();
//                break;
//            }
        }
}

void FrameManager::black_out(Mat &mat){
    for(unsigned int i = 0; i <blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        Mat roi = mat(rec);
        roi = Mat::zeros(rec.height, rec.width, roi.type());
    }
}

void FrameManager::blur(Mat &mat){
    for(unsigned int i = 0; i <blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        Mat roi = mat(rec);
        GaussianBlur(roi, roi, Size(9, 9), 2.5, 2.5);
    }
}

void FrameManager::edge(Mat &mat, const Mat& back){
    Mat sobel_x, sobel_y, sobel;
    for(unsigned int i = 0; i <blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        Mat roi = mat(rec);
        GaussianBlur(roi, roi, Size(7, 7), 1.5, 1.5);
        Sobel(roi, sobel_x, -1, 0, 1);
        Sobel(roi, sobel_y, -1, 1, 0);
        roi = sobel_x+sobel_y+back(rec);
    }
}

cv::Mat FrameManager::QImage2Mat(QImage const& src)
{
     cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cvtColor(tmp, result,CV_BGR2RGB);
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

unsigned int FrameManager::buffered_frame(){
    return buffered_frame_idx;
}
