#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <unistd.h>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    frame_pos   = 0;
    fps         = ui->fps_spinBox->value();
    width       = 0;
    height      = 0;
    alloc_idx   = 0;
    background  = NULL;
    detector    = 0;

    fps_str     = "";
    status_str  = "";
    interval.tv_sec  = 3;
    interval.tv_nsec = 500000000L; //1 000 000 000nsec = 1sec

    fmanager = NULL;

    //clock used to update the label in ui
    lup_timer = new QTimer(this);
    connect(lup_timer, SIGNAL(timeout()), this, SLOT(labelUpdate()));    
}

MainWindow::~MainWindow()
{
    if(fmanager != NULL){
        fmanager->terminate();
        fmanager->quit();
    }

    delete fmanager;
    delete ui;
    exit(0);
}

void MainWindow::on_pushButton_select_clicked()
{
    QFileDialog dialog;

    //QString fileName = dialog.getOpenFileName(this, tr("Open File"), QDir::currentPath(),tr("Videos(*.avi)"));
    QString fileName = dialog.getOpenFileName(this, tr("Open File"), "/home/ren/Videos",tr("Videos(*.avi *.avi.ln)"));
    if(fileName.isEmpty())
        return;

    if(dialog.close() == true)
        process(fileName,false);
}

void MainWindow::setBackground(QImage *background){
    this->background = background;
}

void MainWindow::setDetector(int detector) {
    this->detector = detector;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/ren/Videos",tr("Videos(*.avi *.avi.ln)"));
    if(fileName.isEmpty())
        return;
    process(fileName, false);
}

void MainWindow::on_pushButton_apply_clicked()
{
    if(!cap.isOpened())
        return;
    fps = ui->fps_spinBox->value();
}

void MainWindow::on_actionQuit_triggered()
{
    delete ui;
    exit(0);
}

void MainWindow::process(QString fileName, bool live){

    if(live == false) {
        if(cap.isOpened()){
            cap.release();
            if(wtr.isOpened())
                wtr.release();
            if(fmanager != NULL){
                fmanager->quit();
                delete fmanager;
            }
        }
        cap.open(fileName.toStdString());
    }
    if(live == true) {
        if(cap.isOpened()){
            cap.release();
            if(fmanager != NULL){
                delete fmanager;
            }
        }
        cap.open(0);
    }

    if(cap.isOpened()){
        fmanager = new FrameManager(cap, wtr, ui->spinBox_ctSize, ui->label, ui->label_debug, background);
        connect(fmanager, SIGNAL(processFinished(QImage, QImage)), this, SLOT(imageUpdate(QImage, QImage)));

        fmanager->setLabel(getFocus());
        fmanager->inPrivacy(ui->checkBox_privacy->isChecked());
        fmanager->pain_rect(ui->checkBox_rect->isChecked());
        fmanager->setSigma(ui->doubleSpinBox_gauSigma->value());
        fmanager->setGauSize(ui->spinBox_gauSize->value());
        fmanager->setEdgeThd(ui->spinBox_egThd->value());
        fmanager->setAcuracy(ui->spinBox_polyAcy->value());
        fmanager->setRGBThd(ui->spinBox_rgbCut->value());
        fmanager->setErosion(ui->checkBox_Erosion->isChecked());
        fmanager->setDilate(ui->checkBox_dilate->isChecked());
        fmanager->setRecord(ui->checkBox_record->isChecked());

        if(ui->checkBox_record->isChecked()){
            wtr.open(fileName.append("_rec.avi").toStdString(), CV_FOURCC('H','F','Y','U'),
                     cap.get(CV_CAP_PROP_FPS), Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT)));
        }

        if(detector == MIXGAU_MD) {
            fmanager->setDetector(MIXGAU_MD);
            ui->actionMix_Gaussian_MD->setChecked(true);
            ui->actionOCV_MD->setChecked(false);
            ui->actionOCV_MD->setEnabled(false);
            ui->label_bgModel->setText("Gaussian Mixture");
        } else if(detector == OPENCV_MD) {
            fmanager->setDetector(OPENCV_MD);
            ui->actionOCV_MD->setChecked(true);
            ui->actionMix_Gaussian_MD->setChecked(false);
            ui->actionMix_Gaussian_MD->setEnabled(false);
            ui->label_bgModel->setText("OCV");
        }else {
            if(ui->actionMix_Gaussian_MD->isChecked()) {
                fmanager->setDetector(MIXGAU_MD);
                ui->actionOCV_MD->setChecked(false);
                ui->actionOCV_MD->setEnabled(false);
                ui->label_bgModel->setText("Gaussian Mixture");
            } else if (ui->actionOCV_MD->isChecked()) {
                fmanager->setDetector(OPENCV_MD);
                ui->actionMix_Gaussian_MD->setChecked(false);
                ui->actionMix_Gaussian_MD->setEnabled(false);
                ui->label_bgModel->setText("OCV");
            } else {
                cerr << "operating error: no rio detector selected" << endl;
            }
        }

        if(ui->radioButton_black->isChecked())
            fmanager->setOperat(OP_BLACK);
        else if(ui->radioButton_blur->isChecked())
            fmanager->setOperat(OP_BLUR);
        else if(ui->radioButton_silhouette->isChecked())
            fmanager->setOperat(OP_SILOUETTE);
        else if(ui->radioButton_edge->isChecked())
            fmanager->setOperat(OP_EDGE);
        else if(ui->radioButton_mosaic->isChecked())
            fmanager->setOperat(OP_MOSAIC);
        else if(ui->radioButton_poly->isChecked())
            fmanager->setOperat(OP_POLY);
        else
            fmanager->setOperat(OP_DEFAULT);
        fmanager->start(QThread::NormalPriority);
        lup_timer->start(500);
    } else {
        std::cerr << fileName.toStdString() << " can not be opened" << std::endl;
    }
}

int MainWindow::getFocus() {
    if(ui->radioButton_orig->isChecked())
        return ORIGINAL;
    if(ui->radioButton_color->isChecked())
        return COLOR;
    if(ui->radioButton_grey->isChecked())
        return GREYSCALE;
    if(ui->radioButton_fore->isChecked())
        return FOREGROUND;
    if(ui->radioButton_back->isChecked())
        return BACKGROUND;
    return ORIGINAL;
}

void MainWindow::on_toolButton_play_clicked()
{
    if(fmanager->state() == ST_STOP) {
        fmanager->setState(ST_PROC);
        fmanager->start();
    }
}

void MainWindow::on_toolButton_stop_clicked()
{
    if(fmanager->state() != ST_STOP) {
        fmanager->setState(ST_STOP);
        fmanager->terminate();
    }
}

void MainWindow::on_radioButton_fore_clicked()
{
    if(fmanager != NULL)
        fmanager->setLabel(FOREGROUND);
}

void MainWindow::on_radioButton_back_clicked()
{
    if(fmanager != NULL)
        fmanager->setLabel(BACKGROUND);
}

void MainWindow::on_radioButton_grey_clicked()
{
    if(fmanager != NULL)
        fmanager->setLabel(GREYSCALE);
}

void MainWindow::on_radioButton_orig_clicked()
{
    if(fmanager != NULL)
        fmanager->setLabel(ORIGINAL);
}

void MainWindow::labelUpdate(){
#ifdef MESSAGE_ON
            cout << "@MainWindow.labelUpdate(): 1" << endl;
#endif
    ui->label_fps->setText(QString::number(fps));
    ui->lcdNumber_buffer->display((int)fmanager->frameIndex());
    if(fmanager != NULL) {
        if(fmanager->state() == ST_INIT)
            ui->label_status->setText("init");
        if(fmanager->state() == ST_PROC)
            ui->label_status->setText("working");
        if(fmanager->state() == ST_STOP)
            ui->label_status->setText("stopped");
        if(fmanager->motionDetector() == MIXGAU_MD) {
            ui->label_bgThresh->setText(QString::number(fmanager->bgModelBgThreshold()));
            ui->label_lnRate->setText(QString::number(fmanager->bgModelLearnRate()));
            ui->label_noiseVar->setText(QString::number(fmanager->bgModelNoiseVar()));
            ui->label_sensitivity->setText(QString::number(fmanager->bgModelSensitivity()));
        }

        if(!fmanager->message().isEmpty()){
            QString msg = fmanager->message();
            ui->textBrowser_runMessage->append(msg);
            fmanager->clearMessage();
        }
    } else
        ui->label_status->setText("unknow");

    return;
}

void MainWindow::imageUpdate(QImage image, QImage dbgImage) {
    QPixmap map = QPixmap::fromImage(image);
    if(ui->checkBox_blackOriginal->isChecked())
        map.fill(Qt::black);

    ui->label->setPixmap(map);
    ui->label_debug->setPixmap(QPixmap::fromImage(dbgImage));
}

void MainWindow::on_checkBox_privacy_clicked()
{
    if(fmanager != NULL){
        fmanager->inPrivacy(ui->checkBox_privacy->isChecked());
    }
    return;
}

void MainWindow::on_radioButton_black_clicked()
{
    if(fmanager != NULL)
        fmanager->setOperat(OP_BLACK);
    return;
}

void MainWindow::on_radioButton_blur_clicked()
{
    if(fmanager != NULL)
        fmanager->setOperat(OP_BLUR);
    return;
}

void MainWindow::on_radioButton_edge_clicked()
{
    if(fmanager != NULL)
        fmanager->setOperat(OP_EDGE);
    return;
}

void MainWindow::on_actionOpen_Background_triggered()
{
    QFileDialog dialog;
    QString fileName = dialog.getOpenFileName(this, tr("Open File"), "/home/ren/Videos", tr("Images(*.png *.jpg *.tiff)"));
    if(fileName.isEmpty())
        return;
    background = new QImage(fileName);
    return;
}

void MainWindow::on_radioButton_default_clicked()
{
    if(fmanager != NULL)
        fmanager->setOperat(OP_DEFAULT);
    return;
}

void MainWindow::on_checkBox_rect_clicked()
{
    if(fmanager != NULL)
        fmanager->pain_rect(ui->checkBox_rect->isChecked());
    return;
}

void MainWindow::on_radioButton_mosaic_clicked()
{
    if(fmanager != NULL)
        fmanager->setOperat(OP_MOSAIC);
    return;
}

void MainWindow::on_checkBox_shadow_clicked()
{
    if(fmanager != NULL)
        fmanager->shadow(ui->checkBox_shadow->isChecked());
    return;
}

void MainWindow::on_radioButton_poly_clicked()
{
    if(fmanager != NULL){
        fmanager->setOperat(OP_POLY);
    }
}

void MainWindow::on_actionLIVE_triggered()
{
    process(QString::fromStdString(""), true);
}

void MainWindow::on_spinBox_polyAcy_valueChanged(int arg1)
{
    if(fmanager != NULL){
        fmanager->setAcuracy(ui->spinBox_polyAcy->value());
    }
}

void MainWindow::on_spinBox_moasicSize_valueChanged(int arg1)
{
    if(fmanager != NULL){
        fmanager->setMosaicSize(ui->spinBox_moasicSize->value());
    }
}

void MainWindow::on_doubleSpinBox_gauSigma_valueChanged(double arg1)
{
    if(fmanager != NULL){
        fmanager->setSigma(ui->doubleSpinBox_gauSigma->value());
    }
}

void MainWindow::on_radioButton_color_clicked()
{
        if(fmanager != NULL)
            fmanager->setLabel(COLOR);
}

void MainWindow::on_checkBox_shape_clicked()
{
    if(fmanager != NULL){
        fmanager->setShape(ui->checkBox_shape->isChecked());
    }

}

void MainWindow::on_spinBox_egThd_valueChanged(const QString &arg1)
{
    if(fmanager != NULL)
        fmanager->setEdgeThd(ui->spinBox_egThd->value());
}

void MainWindow::on_spinBox_gauSize_valueChanged(int arg1)
{
    if(fmanager != NULL)
        fmanager->setGauSize(ui->spinBox_gauSize->value());
}

void MainWindow::on_checkBox_greyROI_clicked()
{
    if(fmanager != NULL)
        fmanager->setGreyROI(ui->checkBox_greyROI->isChecked());
}

void MainWindow::on_radioButton_silhouette_clicked()
{
    if(fmanager != NULL)
        fmanager->setOperat(OP_SILOUETTE);

}

void MainWindow::on_actionOCV_MD_triggered()
{
    if(fmanager != NULL && fmanager->state() == ST_INIT) {
        fmanager->setDetector(OPENCV_MD);
    }
}

void MainWindow::on_actionMix_Gaussian_MD_triggered()
{
    if(fmanager != NULL && fmanager->state() == ST_INIT) {
        fmanager->setDetector(MIXGAU_MD);
    }
}

void MainWindow::on_actionFull_Screen_triggered()
{
    if(ui->actionFull_Screen->isChecked() && !ui->label_debug->isFullScreen()) {
        ui->label_debug->setWindowFlags(Qt::Window);
        ui->label_debug->setScaledContents(true);
        ui->label_debug->showFullScreen();
    }
    if(!ui->actionFull_Screen->isChecked() && ui->label_debug->isFullScreen()) {
        ui->label_debug->setWindowFlags(Qt::Widget);
        ui->label_debug->showNormal();
        ui->actionFull_Screen->setChecked(false);
    }
}

void MainWindow::keyPressEvent(QKeyEvent * event) {
    if(ui->label_debug->isFullScreen() && event->key()==Qt::Key_Escape
            && event->type()==QEvent::KeyPress) {
        ui->label_debug->setWindowFlags(Qt::Widget);
        ui->label_debug->showNormal();
        ui->actionFull_Screen->setChecked(false);
    } else
        event->ignore();
}

void MainWindow::on_spinBox_rgbCut_valueChanged(int arg1)
{
    if(fmanager != NULL)
        fmanager->setRGBThd(ui->spinBox_rgbCut->value());
}

void MainWindow::on_checkBox_Erosion_clicked()
{
    if(fmanager != NULL){
        fmanager->setErosion(ui->checkBox_Erosion->isChecked());
        fmanager->setEroSize(ui->spinBox_EroSize->value());
        if(ui->comboBox_EroType->currentText() == "ellipse") {
            fmanager->setEroType(cv::MORPH_ELLIPSE);
        } else if(ui->comboBox_EroType->currentText() == "rectangle") {
            fmanager->setEroType(cv::MORPH_RECT);
        } else if(ui->comboBox_EroType->currentText() == "cross") {
            fmanager->setEroType(cv::MORPH_CROSS);
        } else
            fmanager->setEroType(cv::MORPH_CROSS);
    }
}

void MainWindow::on_comboBox_EroType_textChanged(const QString &arg1)
{
    if(fmanager != NULL){
        if(ui->comboBox_EroType->currentText() == "ellipse") {
            fmanager->setEroType(cv::MORPH_ELLIPSE);
        } else if(ui->comboBox_EroType->currentText() == "rectangle") {
            fmanager->setEroType(cv::MORPH_RECT);
        } else if(ui->comboBox_EroType->currentText() == "cross") {
            fmanager->setEroType(cv::MORPH_CROSS);
        } else
            fmanager->setEroType(cv::MORPH_CROSS);
    }
}

void MainWindow::on_spinBox_EroSize_valueChanged(int arg1)
{
    if(fmanager != NULL){
        fmanager->setEroSize(ui->spinBox_EroSize->value());
    }
}

void MainWindow::on_radioButton_debug_clicked()
{
    if(fmanager != NULL)
        fmanager->setLabel(DEBUG);
}

void MainWindow::on_checkBox_dilate_clicked()
{
    if(fmanager != NULL){
        fmanager->setDilate(ui->checkBox_dilate->isChecked());
        fmanager->setDilSize(ui->spinBox_DilSize->value());
        if(ui->comboBox_DilType->currentText() == "ellipse") {
            fmanager->setDilType(cv::MORPH_ELLIPSE);
        } else if(ui->comboBox_DilType->currentText() == "rectangle") {
            fmanager->setDilType(cv::MORPH_RECT);
        } else if(ui->comboBox_DilType->currentText() == "cross") {
            fmanager->setDilType(cv::MORPH_CROSS);
        } else
            fmanager->setDilType(cv::MORPH_CROSS);
    }
}

void MainWindow::on_comboBox_DilType_textChanged(const QString &arg1)
{
    if(fmanager != NULL){
        if(ui->comboBox_DilType->currentText() == "ellipse") {
            fmanager->setDilType(cv::MORPH_ELLIPSE);
        } else if(ui->comboBox_DilType->currentText() == "rectangle") {
            fmanager->setDilType(cv::MORPH_RECT);
        } else if(ui->comboBox_DilType->currentText() == "cross") {
            fmanager->setDilType(cv::MORPH_CROSS);
        } else
            fmanager->setDilType(cv::MORPH_CROSS);
    }
}

void MainWindow::on_spinBox_DilSize_valueChanged(int arg1)
{
    if(fmanager != NULL)
        fmanager->setDilSize(ui->spinBox_DilSize->value());
}

void MainWindow::on_checkBox_record_clicked()
{
    if(fmanager != NULL)
        fmanager->setRecord(ui->checkBox_record->isChecked());
}
