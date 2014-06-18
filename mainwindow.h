#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "blober.h"
#include "framemanager.h"

//#define DEBUG
#define FMANAGER
#define PLAYER

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    virtual void keyPressEvent(QKeyEvent *event);
private slots:
    void on_pushButton_select_clicked();

    void on_actionOpen_triggered();

    void on_pushButton_apply_clicked();

private:
    Ui::MainWindow *ui;


    QImage* background;
    QTimer* lup_timer;

    QString fps_str;
    QString status_str;

    cv::VideoCapture cap;
    cv::VideoWriter wtr;
    FrameManager* fmanager;
    Blober blober;

    int detector;

    int frame_pos;
    unsigned int alloc_idx;
    unsigned int buffered_frame_idx;

    int fps;
    int width;
    int height;
    timespec interval;
    void *play_function(void *arg);
    void play();
    void stop();

public:
    void process(QString fileName, bool live);
    void setBackground(QImage* background);
    void setDetector(int detector);

private:
    int getFocus();

    private slots:
    void labelUpdate();
    void imageUpdate(QImage image, QImage dbgImage);
    void on_actionQuit_triggered();
    void on_toolButton_play_clicked();
    void on_toolButton_stop_clicked();
    void on_radioButton_fore_clicked();
    void on_radioButton_back_clicked();
    void on_radioButton_grey_clicked();
    void on_radioButton_orig_clicked();
    void on_checkBox_privacy_clicked();
    void on_radioButton_black_clicked();
    void on_radioButton_blur_clicked();
    void on_radioButton_edge_clicked();
    void on_actionOpen_Background_triggered();
    void on_radioButton_default_clicked();
    void on_checkBox_rect_clicked();
    void on_radioButton_mosaic_clicked();
    void on_checkBox_shadow_clicked();
    void on_radioButton_poly_clicked();
    void on_actionLIVE_triggered();
    void on_spinBox_polyAcy_valueChanged(int arg1);
    void on_spinBox_moasicSize_valueChanged(int arg1);
    void on_doubleSpinBox_gauSigma_valueChanged(double arg1);
    void on_radioButton_color_clicked();
    void on_checkBox_shape_clicked();
    void on_spinBox_egThd_valueChanged(const QString &arg1);
    void on_spinBox_gauSize_valueChanged(int arg1);
    void on_checkBox_greyROI_clicked();
    void on_radioButton_silhouette_clicked();
    void on_actionOCV_MD_triggered();
    void on_actionMix_Gaussian_MD_triggered();
    void on_actionFull_Screen_triggered();
    void on_spinBox_rgbCut_valueChanged(int arg1);
    void on_checkBox_Erosion_clicked();
    void on_comboBox_EroType_textChanged(const QString &arg1);
    void on_spinBox_EroSize_valueChanged(int arg1);
    void on_radioButton_debug_clicked();
    void on_checkBox_dilate_clicked();
    void on_comboBox_DilType_textChanged(const QString &arg1);
    void on_spinBox_DilSize_valueChanged(int arg1);
    void on_checkBox_record_clicked();
};

#endif // MAINWINDOW_H
