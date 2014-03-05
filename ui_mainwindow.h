/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Mar 5 17:50:26 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionQuit;
    QAction *actionOpen_Background;
    QAction *actionLIVE;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLabel *label_fps;
    QLabel *label_4;
    QLabel *label_status;
    QLCDNumber *lcdNumber_buffer;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    QSpinBox *spinBox_ctSize;
    QToolButton *toolButton_play;
    QToolButton *toolButton_stop;
    QLabel *label_2;
    QSpinBox *fps_spinBox;
    QPushButton *pushButton_apply;
    QPushButton *pushButton_select;
    QPushButton *pushButton_live;
    QPushButton *pushButton_work;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_debug;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_lockImage;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox_shadow;
    QCheckBox *checkBox_rect;
    QRadioButton *radioButton_orig;
    QRadioButton *radioButton_back;
    QRadioButton *radioButton_fore;
    QRadioButton *radioButton_color;
    QRadioButton *radioButton_grey;
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout;
    QSpinBox *spinBox_egThd;
    QRadioButton *radioButton_poly;
    QSpinBox *spinBox_polyAcy;
    QCheckBox *checkBox_privacy;
    QRadioButton *radioButton_mosaic;
    QRadioButton *radioButton_blur;
    QRadioButton *radioButton_edge;
    QSpacerItem *verticalSpacer;
    QSpinBox *spinBox_moasicSize;
    QDoubleSpinBox *doubleSpinBox_gauSigma;
    QCheckBox *checkBox_shape;
    QRadioButton *radioButton_border;
    QRadioButton *radioButton_black;
    QRadioButton *radioButton_default;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1204, 520);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionOpen_Background = new QAction(MainWindow);
        actionOpen_Background->setObjectName(QString::fromUtf8("actionOpen_Background"));
        actionLIVE = new QAction(MainWindow);
        actionLIVE->setObjectName(QString::fromUtf8("actionLIVE"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 420, 1021, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        label_fps = new QLabel(horizontalLayoutWidget);
        label_fps->setObjectName(QString::fromUtf8("label_fps"));

        horizontalLayout->addWidget(label_fps);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        label_status = new QLabel(horizontalLayoutWidget);
        label_status->setObjectName(QString::fromUtf8("label_status"));

        horizontalLayout->addWidget(label_status);

        lcdNumber_buffer = new QLCDNumber(horizontalLayoutWidget);
        lcdNumber_buffer->setObjectName(QString::fromUtf8("lcdNumber_buffer"));

        horizontalLayout->addWidget(lcdNumber_buffer);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        spinBox_ctSize = new QSpinBox(horizontalLayoutWidget);
        spinBox_ctSize->setObjectName(QString::fromUtf8("spinBox_ctSize"));
        spinBox_ctSize->setMaximum(999);
        spinBox_ctSize->setSingleStep(10);
        spinBox_ctSize->setValue(120);

        horizontalLayout->addWidget(spinBox_ctSize);

        toolButton_play = new QToolButton(horizontalLayoutWidget);
        toolButton_play->setObjectName(QString::fromUtf8("toolButton_play"));

        horizontalLayout->addWidget(toolButton_play);

        toolButton_stop = new QToolButton(horizontalLayoutWidget);
        toolButton_stop->setObjectName(QString::fromUtf8("toolButton_stop"));

        horizontalLayout->addWidget(toolButton_stop);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        fps_spinBox = new QSpinBox(horizontalLayoutWidget);
        fps_spinBox->setObjectName(QString::fromUtf8("fps_spinBox"));
        fps_spinBox->setValue(5);

        horizontalLayout->addWidget(fps_spinBox);

        pushButton_apply = new QPushButton(horizontalLayoutWidget);
        pushButton_apply->setObjectName(QString::fromUtf8("pushButton_apply"));

        horizontalLayout->addWidget(pushButton_apply);

        pushButton_select = new QPushButton(horizontalLayoutWidget);
        pushButton_select->setObjectName(QString::fromUtf8("pushButton_select"));

        horizontalLayout->addWidget(pushButton_select);

        pushButton_live = new QPushButton(horizontalLayoutWidget);
        pushButton_live->setObjectName(QString::fromUtf8("pushButton_live"));
        pushButton_live->setEnabled(false);

        horizontalLayout->addWidget(pushButton_live);

        pushButton_work = new QPushButton(horizontalLayoutWidget);
        pushButton_work->setObjectName(QString::fromUtf8("pushButton_work"));

        horizontalLayout->addWidget(pushButton_work);

        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 30, 1021, 391));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(507, 389));
        label->setMaximumSize(QSize(507, 389));
        label->setStyleSheet(QString::fromUtf8("border-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));
        label->setScaledContents(true);

        horizontalLayout_2->addWidget(label);

        label_debug = new QLabel(horizontalLayoutWidget_2);
        label_debug->setObjectName(QString::fromUtf8("label_debug"));
        sizePolicy.setHeightForWidth(label_debug->sizePolicy().hasHeightForWidth());
        label_debug->setSizePolicy(sizePolicy);
        label_debug->setMinimumSize(QSize(506, 389));
        label_debug->setMaximumSize(QSize(506, 389));
        label_debug->setScaledContents(true);

        horizontalLayout_2->addWidget(label_debug);

        horizontalLayoutWidget_3 = new QWidget(centralWidget);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(0, 0, 1171, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        checkBox_lockImage = new QCheckBox(horizontalLayoutWidget_3);
        checkBox_lockImage->setObjectName(QString::fromUtf8("checkBox_lockImage"));
        checkBox_lockImage->setChecked(true);

        horizontalLayout_3->addWidget(checkBox_lockImage);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        checkBox_shadow = new QCheckBox(horizontalLayoutWidget_3);
        checkBox_shadow->setObjectName(QString::fromUtf8("checkBox_shadow"));
        checkBox_shadow->setChecked(false);

        horizontalLayout_3->addWidget(checkBox_shadow);

        checkBox_rect = new QCheckBox(horizontalLayoutWidget_3);
        checkBox_rect->setObjectName(QString::fromUtf8("checkBox_rect"));
        checkBox_rect->setChecked(true);

        horizontalLayout_3->addWidget(checkBox_rect);

        radioButton_orig = new QRadioButton(horizontalLayoutWidget_3);
        radioButton_orig->setObjectName(QString::fromUtf8("radioButton_orig"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(radioButton_orig->sizePolicy().hasHeightForWidth());
        radioButton_orig->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(radioButton_orig);

        radioButton_back = new QRadioButton(horizontalLayoutWidget_3);
        radioButton_back->setObjectName(QString::fromUtf8("radioButton_back"));

        horizontalLayout_3->addWidget(radioButton_back);

        radioButton_fore = new QRadioButton(horizontalLayoutWidget_3);
        radioButton_fore->setObjectName(QString::fromUtf8("radioButton_fore"));
        radioButton_fore->setChecked(false);

        horizontalLayout_3->addWidget(radioButton_fore);

        radioButton_color = new QRadioButton(horizontalLayoutWidget_3);
        radioButton_color->setObjectName(QString::fromUtf8("radioButton_color"));

        horizontalLayout_3->addWidget(radioButton_color);

        radioButton_grey = new QRadioButton(horizontalLayoutWidget_3);
        radioButton_grey->setObjectName(QString::fromUtf8("radioButton_grey"));
        radioButton_grey->setChecked(true);

        horizontalLayout_3->addWidget(radioButton_grey);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(1020, 30, 182, 391));
        gridLayout = new QGridLayout(verticalLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        spinBox_egThd = new QSpinBox(verticalLayoutWidget);
        spinBox_egThd->setObjectName(QString::fromUtf8("spinBox_egThd"));
        spinBox_egThd->setMaximum(255);
        spinBox_egThd->setSingleStep(5);
        spinBox_egThd->setValue(15);

        gridLayout->addWidget(spinBox_egThd, 4, 1, 1, 1);

        radioButton_poly = new QRadioButton(verticalLayoutWidget);
        radioButton_poly->setObjectName(QString::fromUtf8("radioButton_poly"));

        gridLayout->addWidget(radioButton_poly, 7, 0, 1, 1);

        spinBox_polyAcy = new QSpinBox(verticalLayoutWidget);
        spinBox_polyAcy->setObjectName(QString::fromUtf8("spinBox_polyAcy"));
        spinBox_polyAcy->setMinimum(5);
        spinBox_polyAcy->setMaximum(9);
        spinBox_polyAcy->setSingleStep(2);

        gridLayout->addWidget(spinBox_polyAcy, 7, 1, 1, 1);

        checkBox_privacy = new QCheckBox(verticalLayoutWidget);
        checkBox_privacy->setObjectName(QString::fromUtf8("checkBox_privacy"));
        checkBox_privacy->setChecked(true);

        gridLayout->addWidget(checkBox_privacy, 1, 0, 1, 2);

        radioButton_mosaic = new QRadioButton(verticalLayoutWidget);
        radioButton_mosaic->setObjectName(QString::fromUtf8("radioButton_mosaic"));

        gridLayout->addWidget(radioButton_mosaic, 9, 0, 1, 1);

        radioButton_blur = new QRadioButton(verticalLayoutWidget);
        radioButton_blur->setObjectName(QString::fromUtf8("radioButton_blur"));
        radioButton_blur->setChecked(true);

        gridLayout->addWidget(radioButton_blur, 3, 0, 1, 1);

        radioButton_edge = new QRadioButton(verticalLayoutWidget);
        radioButton_edge->setObjectName(QString::fromUtf8("radioButton_edge"));

        gridLayout->addWidget(radioButton_edge, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 0, 1, 1);

        spinBox_moasicSize = new QSpinBox(verticalLayoutWidget);
        spinBox_moasicSize->setObjectName(QString::fromUtf8("spinBox_moasicSize"));
        spinBox_moasicSize->setMinimum(10);
        spinBox_moasicSize->setMaximum(30);
        spinBox_moasicSize->setSingleStep(10);

        gridLayout->addWidget(spinBox_moasicSize, 9, 1, 1, 1);

        doubleSpinBox_gauSigma = new QDoubleSpinBox(verticalLayoutWidget);
        doubleSpinBox_gauSigma->setObjectName(QString::fromUtf8("doubleSpinBox_gauSigma"));
        doubleSpinBox_gauSigma->setMinimum(2.5);
        doubleSpinBox_gauSigma->setMaximum(10);
        doubleSpinBox_gauSigma->setSingleStep(2.5);

        gridLayout->addWidget(doubleSpinBox_gauSigma, 3, 1, 1, 1);

        checkBox_shape = new QCheckBox(verticalLayoutWidget);
        checkBox_shape->setObjectName(QString::fromUtf8("checkBox_shape"));

        gridLayout->addWidget(checkBox_shape, 11, 1, 1, 1);

        radioButton_border = new QRadioButton(verticalLayoutWidget);
        radioButton_border->setObjectName(QString::fromUtf8("radioButton_border"));

        gridLayout->addWidget(radioButton_border, 10, 0, 1, 1);

        radioButton_black = new QRadioButton(verticalLayoutWidget);
        radioButton_black->setObjectName(QString::fromUtf8("radioButton_black"));
        radioButton_black->setChecked(false);

        gridLayout->addWidget(radioButton_black, 10, 1, 1, 1);

        radioButton_default = new QRadioButton(verticalLayoutWidget);
        radioButton_default->setObjectName(QString::fromUtf8("radioButton_default"));
        radioButton_default->setChecked(false);

        gridLayout->addWidget(radioButton_default, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1204, 27));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionOpen_Background);
        menuFile->addAction(actionLIVE);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionOpen_Background->setText(QApplication::translate("MainWindow", "Open Background", 0, QApplication::UnicodeUTF8));
        actionOpen_Background->setShortcut(QApplication::translate("MainWindow", "Ctrl+B", 0, QApplication::UnicodeUTF8));
        actionLIVE->setText(QApplication::translate("MainWindow", "LIVE", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "FPS:", 0, QApplication::UnicodeUTF8));
        label_fps->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Status:", 0, QApplication::UnicodeUTF8));
        label_status->setText(QApplication::translate("MainWindow", "No Input", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Contour Size", 0, QApplication::UnicodeUTF8));
        toolButton_play->setText(QApplication::translate("MainWindow", "play", 0, QApplication::UnicodeUTF8));
        toolButton_stop->setText(QApplication::translate("MainWindow", "stop", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "FPS", 0, QApplication::UnicodeUTF8));
        pushButton_apply->setText(QApplication::translate("MainWindow", "apply", 0, QApplication::UnicodeUTF8));
        pushButton_select->setText(QApplication::translate("MainWindow", "select", 0, QApplication::UnicodeUTF8));
        pushButton_live->setText(QApplication::translate("MainWindow", "LIVE", 0, QApplication::UnicodeUTF8));
        pushButton_work->setText(QApplication::translate("MainWindow", "Halt", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_debug->setText(QString());
        checkBox_lockImage->setText(QApplication::translate("MainWindow", "Lock", 0, QApplication::UnicodeUTF8));
        checkBox_shadow->setText(QApplication::translate("MainWindow", "shadowDet", 0, QApplication::UnicodeUTF8));
        checkBox_rect->setText(QApplication::translate("MainWindow", "rectangle", 0, QApplication::UnicodeUTF8));
        radioButton_orig->setText(QApplication::translate("MainWindow", "original", 0, QApplication::UnicodeUTF8));
        radioButton_back->setText(QApplication::translate("MainWindow", "background", 0, QApplication::UnicodeUTF8));
        radioButton_fore->setText(QApplication::translate("MainWindow", "foreground", 0, QApplication::UnicodeUTF8));
        radioButton_color->setText(QApplication::translate("MainWindow", "color", 0, QApplication::UnicodeUTF8));
        radioButton_grey->setText(QApplication::translate("MainWindow", "grey", 0, QApplication::UnicodeUTF8));
        radioButton_poly->setText(QApplication::translate("MainWindow", "poly", 0, QApplication::UnicodeUTF8));
        checkBox_privacy->setText(QApplication::translate("MainWindow", "anonymous mode", 0, QApplication::UnicodeUTF8));
        radioButton_mosaic->setText(QApplication::translate("MainWindow", "mosaic", 0, QApplication::UnicodeUTF8));
        radioButton_blur->setText(QApplication::translate("MainWindow", "blur", 0, QApplication::UnicodeUTF8));
        radioButton_edge->setText(QApplication::translate("MainWindow", "edge", 0, QApplication::UnicodeUTF8));
        checkBox_shape->setText(QApplication::translate("MainWindow", "shape", 0, QApplication::UnicodeUTF8));
        radioButton_border->setText(QApplication::translate("MainWindow", "border", 0, QApplication::UnicodeUTF8));
        radioButton_black->setText(QApplication::translate("MainWindow", "black", 0, QApplication::UnicodeUTF8));
        radioButton_default->setText(QApplication::translate("MainWindow", "default", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
