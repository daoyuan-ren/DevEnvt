#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>

#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>
#include <fstream>
#include <vector>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "playthread.h"

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

    QList<QImage> imgBuffer;
    QList<QImage> dbgBuffer;

    QPixmap* pixMap;
    QMovie* movie;

    QTimer* timer;

    QString fps_str;
    QString status_str;

    cv::VideoCapture cap;

    pthread_t thread1;
    PlayThread* player;

    int frame_ctr;
    int fps;
    int width;
    int height;
    timespec interval;

    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);

    void *play_function(void *arg);
    void play();
    void stop();

    private slots:
    void imageUpdate();
    void on_actionQuit_triggered();
};

#endif // MAINWINDOW_H
