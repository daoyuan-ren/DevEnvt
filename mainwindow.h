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

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "playthread.h"
#include "blober.h"
#include "framemanager.h"

#define DEBUG

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_select_clicked();

    void on_actionOpen_triggered();

    void on_pushButton_apply_clicked();

private:
    Ui::MainWindow *ui;

    QList<QImage>* imgBuffer;
    QList<QImage>* dbgBuffer;
    QList<QImage>* backBuffer;
    QList<QImage>  swap;
    QTimer* mem_timer;
    QTimer* lup_timer;

    QString fps_str;
    QString status_str;

    cv::VideoCapture cap;

    PlayThread* player;
    FrameManager* fmanager;

    BackgroundSubtractorMOG2 bg;
//    vector< vector<Point> > contours;
//    vector< vector<Point> > bigcons;
    Blober blober;
//    FrameManager* fmanager;

    int frame_pos;
    unsigned int alloc_idx;
    unsigned int buffered_frame_idx;

    int fps;
    int width;
    int height;
    timespec interval;

    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);

    void *play_function(void *arg);
    void play();
    void stop();

//    Blob findBlobs(Mat& frame, Mat& drawing, int blob_minSize);
    void paintBlobs(QImage* frame, Blober& blober);
    void process(QString fileName, bool live);

    private slots:
    void imageUpdate();
    void labelUpdate();
    void memManage();
    void on_actionQuit_triggered();
    void on_toolButton_play_clicked();
    void on_toolButton_stop_clicked();
    void on_pushButton_live_clicked();
    void on_radioButton_fore_clicked();
    void on_radioButton_back_clicked();
    void on_radioButton_grey_clicked();
    void on_radioButton_orig_clicked();
};

#endif // MAINWINDOW_H
