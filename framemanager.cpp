#include "framemanager.h"
#include "package_bgs/lb/LBMixtureOfGaussians.h"

FrameManager::FrameManager(QObject *parent) :
    QThread(parent)
{
    interval.tv_sec     = 0;
    interval.tv_nsec    = 300000000L; //1 000 000 000nsec = 1sec
    frame_idx           = 0;
    in_privacy_mode     = false;
    pain_blob           = true;
    shadow_detect       = false;
    with_shape          = false;
    //pixel_operation     = OP_DEFAULT;
    poly_acuracy        = 1;
    edge_thd            = 15;
    rgb_thd          = 40;

    state_t             = ST_INIT;

    bg.set("nmixtures", 3);
    bg.set("history", HISTORY);
//    bg.bShadowDetection = true;
    bg.set("detectShadows", true);

    bgs                 = NULL;

    static_background   = NULL;

    spinBox_ctSize      = NULL;
}

FrameManager::FrameManager(VideoCapture cap, VideoWriter& wtr, QSpinBox* spinBox_ctSize,
                           QLabel* imgLabel, QLabel* dbgLabel, QImage* s_back){
        interval.tv_sec     = 0;
        interval.tv_nsec    = 300000000L; //1 000 000 000nsec = 1sec
        frame_idx           = 0;
        in_privacy_mode     = false;
        pain_blob           = true;
        shadow_detect       = false;
        with_shape          = false;
        grey_roi            = false;
        erosion             = false;
        dilation            = false;
        record              = false;
        morph_colse         = true;
        //pixel_operation     = OP_DEFAULT;
        poly_acuracy        = 1;
        mosaic_size         = 10;
        gau_size            = 9;
        gau_sigma           = 2.5;
        edge_thd            = 15;
        egGau_sigma         = 0;
        ero_size            = 3;
        ero_type            = cv::MORPH_CROSS;
        dil_size            = 3;
        ero_type            = cv::MORPH_CROSS;
        mcl_size            = 7;
        mcl_type            = cv::MORPH_CROSS;


        working_md          = MIXGAU_MD;
        state_t             = ST_INIT;
//        timer               = new QTimer(0);
//        connect(timer_ptr, SIGNAL(timeout()), this, SLOT(imageUpdate()));

        bg.set("nmixtures", 3);
        bg.set("history", HISTORY);
        bg.set("detectShadows", true);

        bgs                 = NULL;

        this->cap           = cap;
        this->wtr           = wtr;
        static_background   = s_back;

        this->spinBox_ctSize = spinBox_ctSize;
        this->imgLabel = imgLabel;
        this->dbgLabel = dbgLabel;
}

FrameManager::~FrameManager(){
    terminate();

    if(static_background != NULL)
        delete static_background;
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

void FrameManager::setGreyROI(bool grey_roi) {
    this->grey_roi = grey_roi;
}

void FrameManager::setErosion(bool erosion) {
    this->erosion = erosion;
}

void FrameManager::setDilate(bool dilate){
    this->dilation = dilate;
}

void FrameManager::setClose(bool close){
    this->morph_colse = close;
}

void FrameManager::setRecord(bool record){
    this->record = record;
}

void FrameManager::setGauSize(int gau_size) {
    this->gau_size = gau_size;
}

void FrameManager::setEdgeThd(int edge_thd){
    if(edge_thd >= 0 && edge_thd <= 255)
        this->edge_thd = edge_thd;
}

void FrameManager::setLabel(int lbl) {
    label_t = lbl;
}

void FrameManager::setDetector(int working_md) {
    this->working_md = working_md;
}

void FrameManager::setRGBThd(int rgbThd) {
    rgb_thd = rgbThd >= 0 && rgbThd <= 255 ? rgbThd : rgb_thd;
}

void FrameManager::setMclSize(int mclSize) {
    this->mcl_size = mclSize;
}

void FrameManager::setMclType(int mclType){
    this->mcl_type = mclType;
}

void FrameManager::setEroSize(int size) {
    ero_size = size;
}

void FrameManager::setEroType(int type){
    ero_type = type;
}

void FrameManager::setDilSize(int size){
    dil_size = size;
}

void FrameManager::setDilType(int type){
    dil_type = type;
}

void FrameManager::setEgGauSigma(double egGau_sigma) {
    this->egGau_sigma = egGau_sigma;
}

int FrameManager::state(){
   return this->state_t;
}

int FrameManager::label() {
    return label_t;
}

int FrameManager::motionDetector() {
    return working_md;
}

int FrameManager::bgModelSensitivity() {
    if(working_md == MIXGAU_MD && bgs != NULL)
        return bgs->getSensitivity();
}

int FrameManager::bgModelBgThreshold() {
    if(working_md == MIXGAU_MD && bgs != NULL)
        return bgs->getBgThreshold();
}

int FrameManager::bgModelLearnRate() {
    if(working_md == MIXGAU_MD && bgs != NULL)
        return bgs->getlearningRt();
}

int FrameManager::bgModelNoiseVar() {
    if(working_md == MIXGAU_MD && bgs != NULL)
        return bgs->getNoiseVar();
}

QString FrameManager::message() {
    return runningMessage;
}

void FrameManager::addMessage(QString message) {
    msgMutex.lock();
    runningMessage.append(message);
    msgMutex.unlock();
}

void FrameManager::clearMessage() {
    msgMutex.lock();
    runningMessage.clear();
    msgMutex.unlock();
}

void FrameManager::process(){
#ifdef MESSAGE_ON
    cout << "start to process" << endl;
    cout << "@fmanager.process(): " << currentThreadId() << endl;
#endif
//        fps     = cap.get(CV_CAP_PROP_FPS);
//        width   = cap.get(CV_CAP_PROP_FRAME_WIDTH);
//        height  = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

        Mat frame, frame_gau, back, fore, fore_contours;
        Mat drawing, grey, grey_back, st_back, st_back_grey;
        QImage image, clr_image, grey_image, fore_ground, back_ground, debug_image;
        bgs = new LBMixtureOfGaussians;

        if(working_md == MIXGAU_MD)
            addMessage("LBMixtureOfGaussians()\n");
        if(working_md == OPENCV_MD)
            addMessage("BackgroundSubtractorMOG2()\n");

        for(frame_idx = 0;; frame_idx++) {
            cap >> frame;
            if(frame.empty())
                break;
            cvtColor(frame, grey, CV_RGB2GRAY);
            cvtColor(grey, grey, CV_GRAY2BGR);
            image = Mat2QImage(frame);

            GaussianBlur(frame, frame_gau, Size(5, 5), 1.5, 1.5);

            /*** subtracting backgrounds from frame using different algorithms ***/
            if(working_md == OPENCV_MD) {
                bg.operator ()(frame_gau, fore, 0.01);
                bg.getBackgroundImage(back);
                threshold(fore, fore, 128, 255, THRESH_BINARY);
            }

            /*** in case using the LBMixtureOfGaussianDetector ***/
            if(working_md == MIXGAU_MD) {
                bgs->process(frame_gau, fore, back);
                cvtColor(fore, fore, CV_RGB2GRAY);
            }

            fore.copyTo(fore_contours);
            if(shadow_detect == true)
                rgbCut(fore_contours, frame, back, rgb_thd);
            if(erosion == true)
                erode(fore_contours, fore_contours, getStructuringElement(ero_type, Size(ero_size, ero_size), Point(0, 0)));

            if(dilation == true)
                dilate(fore_contours, fore_contours, getStructuringElement(dil_type, Size(dil_size, dil_size), Point(0, 0)));

            cvtColor(fore, drawing, CV_GRAY2BGR);
            if(morph_colse == true)
                morphologyEx(drawing, drawing, MORPH_CLOSE, getStructuringElement(mcl_type,Size(mcl_size,mcl_size)));

            blober.find_blobs(fore_contours, spinBox_ctSize->value(), shadow_detect, poly_acuracy);
            cvtColor(back, grey_back, CV_RGB2GRAY);
            cvtColor(grey_back, grey_back, CV_GRAY2BGR);

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
                    edge(drawing, grey, back, grey_back, st_back, st_back_grey);
                    break;
                case OP_SILOUETTE:
                    silouette(drawing, back, grey_back, st_back, st_back_grey);
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
                blober.paint_blobs(fore_contours, PT_RECT, CL_GREEN);
            }
            if(record == true)
                wtr << st_back;
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
            QString blobInfo = blober.paint_label(&fore_ground);
            back_ground = Mat2QImage(back);
            clr_image   = Mat2QImage(st_back);
            grey_image  = Mat2QImage(st_back_grey);
            debug_image = Mat2QImage(fore_contours);

            addMessage(blobInfo);
#ifdef LABEL_ON
            if(pain_blob == true){
                blober.paint_label(&back_ground);
                blober.paint_label(&clr_image);
                blober.paint_label(&grey_image);
//                blober.paint_label(&debug_image);
            }
#endif
            try{
                switch(label_t) {
                case ORIGINAL:
                    emit processFinished(image, image);
                    break;
                case COLOR:
                    emit processFinished(image, clr_image);
                    break;
                case GREYSCALE:
                    emit processFinished(image, grey_image);
                    break;
                case BACKGROUND:
                    emit processFinished(image, back_ground);
                    break;
                case FOREGROUND:
                    emit processFinished(image, fore_ground);
                    break;
                case DEBUG:
                    emit processFinished(image, debug_image);
                default:
                    break;
                }
            } catch(std::bad_alloc& balc){
                cerr << "bad allocation caught at " << frame_idx << "th frame." << endl;
            }
#ifdef MESSAGE_ON
            cout << "<" << buffered_frame_idx << "> " << "processing @fmanager.run(): " << currentThreadId() << endl;
#endif
            if(state_t == ST_PROC){
                nanosleep(&interval, NULL);
            }
            else
                sleep(3);
        }
        wtr.release();
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
        Mat roi             = mat(rec);
        Mat roi_grey        = grey(rec);
        Mat mask            = fore(rec);
        Mat roi_back        = st_back(rec);
        Mat roi_back_grey   = st_back_grey(rec);
        Mat roi_gau, roi_grey_gau, inv_mask;

        GaussianBlur(roi, roi_gau, Size(gau_size, gau_size), gau_sigma, gau_sigma);
        GaussianBlur(roi_grey, roi_grey_gau, Size(gau_size, gau_size), gau_sigma, gau_sigma);

        if(grey_roi == true) {
            cvtColor(roi_gau, roi_gau, CV_RGB2GRAY);
            cvtColor(roi_gau, roi_gau, CV_GRAY2RGB);
        }

        bitwise_and(roi_gau,mask,roi_gau);
        bitwise_and(roi_grey_gau,mask,roi_grey_gau);
        bitwise_not(mask, inv_mask);
        bitwise_and(roi_back,inv_mask,roi_back);
        bitwise_and(roi_back_grey,inv_mask,roi_back_grey);
        roi_back += roi_gau;
        roi_back_grey += roi_grey_gau;
        roi_back.copyTo(st_back(rec));
        roi_back_grey.copyTo(st_back_grey(rec));
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

void FrameManager::edge(Mat &fore, Mat& grey, const Mat& back, const Mat& grey_back, Mat& st_back, Mat& st_back_grey){
    Mat sobel_x, sobel_y, sobel;
    for(unsigned int i = 0; i < blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        if(rec.width <= 0 || rec.height <= 0)
            continue;
        Mat roi_grey = grey(rec);
        Mat mask = fore(rec);
        Mat roi_back = st_back(rec);
        Mat roi_back_grey = st_back_grey(rec);
        cvtColor(roi_grey, roi_grey, CV_BGR2GRAY);
        GaussianBlur(roi_grey, roi_grey, Size(7, 7), 1.5, 1.5);
        Sobel(roi_grey, sobel_x, -1, 0, 1);
        Sobel(roi_grey, sobel_y, -1, 1, 0);
        sobel = sobel_x + sobel_y;
        threshold(sobel, sobel, edge_thd, 255, THRESH_TOZERO);
        GaussianBlur(sobel, sobel, Size(7, 7), egGau_sigma, egGau_sigma);
        cvtColor(sobel, sobel, CV_GRAY2BGR);

        bitwise_and(sobel, mask, sobel);
        roi_back += sobel;
        roi_back_grey += sobel;
    }
    if(with_shape)
        poly(st_back, st_back_grey, CL_SKY);
}

void FrameManager::silouette(const Mat& fore, const Mat& back, const Mat& grey_back, Mat& st_back, Mat& st_back_grey){
    for(unsigned int i = 0; i <blober.rects()->size(); i++){
        Rect rec = blober.rects()->at(i);
        if(rec.width <= 0 || rec.height <= 0)
            continue;
        Mat frec = fore(rec);
        Mat stbrec = st_back(rec);

        Mat frec_inv;
        threshold(frec, frec_inv, 128, 1, THRESH_BINARY_INV);
        st_back(rec) = stbrec.mul(frec_inv);
        st_back_grey(rec) = grey_back(rec).mul(frec_inv);
    }
}

void FrameManager::rgbCut(Mat &fore, const Mat &mat, const Mat &back, unsigned char thresh) {
    if(fore.empty() || mat.empty() || back.empty())
        return;
    Mat diff;
    Mat channels[3];
    absdiff(mat, back, diff);
    threshold(diff, diff, thresh, 1, cv::THRESH_BINARY);
    split(diff, channels);
    multiply(fore, channels[0], fore);
    multiply(fore, channels[1], fore);
    multiply(fore, channels[2], fore);
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
    setState(ST_PROC);
    process();
}

void FrameManager::gamma_correction(Mat &mat, const double gamma){
    mat = mat * gamma;
}

unsigned int FrameManager::frameIndex(){
    return frame_idx;
}
