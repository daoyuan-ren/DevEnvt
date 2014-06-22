/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Jun 22 17:04:31 2014
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
#include <QtGui/QComboBox>
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
#include <QtGui/QTextBrowser>
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
    QAction *actionOCV_MD;
    QAction *actionMix_Gaussian_MD;
    QAction *actionFull_Screen;
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
    QCheckBox *checkBox_record;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_debug;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_blackOriginal;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox_shadow;
    QSpinBox *spinBox_rgbCut;
    QCheckBox *checkBox_rect;
    QRadioButton *radioButton_orig;
    QRadioButton *radioButton_back;
    QRadioButton *radioButton_fore;
    QRadioButton *radioButton_color;
    QRadioButton *radioButton_grey;
    QRadioButton *radioButton_debug;
    QCheckBox *checkBox_greyROI;
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_mosaic;
    QSpinBox *spinBox_gauSize;
    QSpinBox *spinBox_moasicSize;
    QCheckBox *checkBox_shape;
    QRadioButton *radioButton_black;
    QRadioButton *radioButton_default;
    QRadioButton *radioButton_silhouette;
    QRadioButton *radioButton_edge;
    QCheckBox *checkBox_privacy;
    QRadioButton *radioButton_poly;
    QRadioButton *radioButton_blur;
    QDoubleSpinBox *doubleSpinBox_gauSigma;
    QSpinBox *spinBox_polyAcy;
    QSpinBox *spinBox_egThd;
    QDoubleSpinBox *doubleSpinBox_egGauSigma;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QLabel *label_sensitivity;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_10;
    QLabel *label_bgThresh;
    QLabel *label_lnRate;
    QLabel *label_9;
    QLabel *label_noiseVar;
    QLabel *label_bgModel;
    QTextBrowser *textBrowser_runMessage;
    QCheckBox *checkBox_Erosion;
    QSpinBox *spinBox_EroSize;
    QComboBox *comboBox_EroType;
    QCheckBox *checkBox_dilate;
    QComboBox *comboBox_DilType;
    QSpinBox *spinBox_DilSize;
    QCheckBox *checkBox_morphClose;
    QComboBox *comboBox_mclType;
    QSpinBox *spinBox_mclSize;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1282, 781);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setFocusPolicy(Qt::StrongFocus);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionOpen_Background = new QAction(MainWindow);
        actionOpen_Background->setObjectName(QString::fromUtf8("actionOpen_Background"));
        actionLIVE = new QAction(MainWindow);
        actionLIVE->setObjectName(QString::fromUtf8("actionLIVE"));
        actionOCV_MD = new QAction(MainWindow);
        actionOCV_MD->setObjectName(QString::fromUtf8("actionOCV_MD"));
        actionOCV_MD->setCheckable(true);
        actionMix_Gaussian_MD = new QAction(MainWindow);
        actionMix_Gaussian_MD->setObjectName(QString::fromUtf8("actionMix_Gaussian_MD"));
        actionMix_Gaussian_MD->setCheckable(true);
        actionMix_Gaussian_MD->setChecked(true);
        actionFull_Screen = new QAction(MainWindow);
        actionFull_Screen->setObjectName(QString::fromUtf8("actionFull_Screen"));
        actionFull_Screen->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 690, 1021, 31));
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
        spinBox_ctSize->setValue(150);

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

        checkBox_record = new QCheckBox(horizontalLayoutWidget);
        checkBox_record->setObjectName(QString::fromUtf8("checkBox_record"));
        checkBox_record->setChecked(true);

        horizontalLayout->addWidget(checkBox_record);

        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 30, 1281, 441));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(507, 389));
        label->setStyleSheet(QString::fromUtf8("border-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));
        label->setScaledContents(true);

        horizontalLayout_2->addWidget(label);

        label_debug = new QLabel(horizontalLayoutWidget_2);
        label_debug->setObjectName(QString::fromUtf8("label_debug"));
        sizePolicy1.setHeightForWidth(label_debug->sizePolicy().hasHeightForWidth());
        label_debug->setSizePolicy(sizePolicy1);
        label_debug->setMinimumSize(QSize(506, 389));
        label_debug->setFocusPolicy(Qt::NoFocus);
        label_debug->setScaledContents(true);

        horizontalLayout_2->addWidget(label_debug);

        horizontalLayoutWidget_3 = new QWidget(centralWidget);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(0, 0, 1271, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        checkBox_blackOriginal = new QCheckBox(horizontalLayoutWidget_3);
        checkBox_blackOriginal->setObjectName(QString::fromUtf8("checkBox_blackOriginal"));
        checkBox_blackOriginal->setChecked(true);

        horizontalLayout_3->addWidget(checkBox_blackOriginal);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        checkBox_shadow = new QCheckBox(horizontalLayoutWidget_3);
        checkBox_shadow->setObjectName(QString::fromUtf8("checkBox_shadow"));
        checkBox_shadow->setChecked(false);

        horizontalLayout_3->addWidget(checkBox_shadow);

        spinBox_rgbCut = new QSpinBox(horizontalLayoutWidget_3);
        spinBox_rgbCut->setObjectName(QString::fromUtf8("spinBox_rgbCut"));
        spinBox_rgbCut->setMaximum(255);
        spinBox_rgbCut->setSingleStep(5);
        spinBox_rgbCut->setValue(20);

        horizontalLayout_3->addWidget(spinBox_rgbCut);

        checkBox_rect = new QCheckBox(horizontalLayoutWidget_3);
        checkBox_rect->setObjectName(QString::fromUtf8("checkBox_rect"));
        checkBox_rect->setChecked(false);

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
        radioButton_color->setChecked(true);

        horizontalLayout_3->addWidget(radioButton_color);

        radioButton_grey = new QRadioButton(horizontalLayoutWidget_3);
        radioButton_grey->setObjectName(QString::fromUtf8("radioButton_grey"));
        radioButton_grey->setChecked(false);

        horizontalLayout_3->addWidget(radioButton_grey);

        radioButton_debug = new QRadioButton(horizontalLayoutWidget_3);
        radioButton_debug->setObjectName(QString::fromUtf8("radioButton_debug"));

        horizontalLayout_3->addWidget(radioButton_debug);

        checkBox_greyROI = new QCheckBox(horizontalLayoutWidget_3);
        checkBox_greyROI->setObjectName(QString::fromUtf8("checkBox_greyROI"));

        horizontalLayout_3->addWidget(checkBox_greyROI);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(1020, 470, 261, 251));
        gridLayout = new QGridLayout(verticalLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        radioButton_mosaic = new QRadioButton(verticalLayoutWidget);
        radioButton_mosaic->setObjectName(QString::fromUtf8("radioButton_mosaic"));

        gridLayout->addWidget(radioButton_mosaic, 8, 0, 1, 1);

        spinBox_gauSize = new QSpinBox(verticalLayoutWidget);
        spinBox_gauSize->setObjectName(QString::fromUtf8("spinBox_gauSize"));
        spinBox_gauSize->setMinimum(15);
        spinBox_gauSize->setMaximum(37);
        spinBox_gauSize->setSingleStep(2);
        spinBox_gauSize->setValue(27);

        gridLayout->addWidget(spinBox_gauSize, 2, 1, 1, 1);

        spinBox_moasicSize = new QSpinBox(verticalLayoutWidget);
        spinBox_moasicSize->setObjectName(QString::fromUtf8("spinBox_moasicSize"));
        spinBox_moasicSize->setMinimum(10);
        spinBox_moasicSize->setMaximum(30);
        spinBox_moasicSize->setSingleStep(10);

        gridLayout->addWidget(spinBox_moasicSize, 8, 1, 1, 2);

        checkBox_shape = new QCheckBox(verticalLayoutWidget);
        checkBox_shape->setObjectName(QString::fromUtf8("checkBox_shape"));

        gridLayout->addWidget(checkBox_shape, 9, 2, 1, 1);

        radioButton_black = new QRadioButton(verticalLayoutWidget);
        radioButton_black->setObjectName(QString::fromUtf8("radioButton_black"));
        radioButton_black->setChecked(false);

        gridLayout->addWidget(radioButton_black, 9, 1, 1, 1);

        radioButton_default = new QRadioButton(verticalLayoutWidget);
        radioButton_default->setObjectName(QString::fromUtf8("radioButton_default"));
        radioButton_default->setChecked(false);

        gridLayout->addWidget(radioButton_default, 1, 0, 1, 1);

        radioButton_silhouette = new QRadioButton(verticalLayoutWidget);
        radioButton_silhouette->setObjectName(QString::fromUtf8("radioButton_silhouette"));

        gridLayout->addWidget(radioButton_silhouette, 9, 0, 1, 1);

        radioButton_edge = new QRadioButton(verticalLayoutWidget);
        radioButton_edge->setObjectName(QString::fromUtf8("radioButton_edge"));

        gridLayout->addWidget(radioButton_edge, 3, 0, 1, 1);

        checkBox_privacy = new QCheckBox(verticalLayoutWidget);
        checkBox_privacy->setObjectName(QString::fromUtf8("checkBox_privacy"));
        checkBox_privacy->setChecked(true);

        gridLayout->addWidget(checkBox_privacy, 0, 0, 1, 3);

        radioButton_poly = new QRadioButton(verticalLayoutWidget);
        radioButton_poly->setObjectName(QString::fromUtf8("radioButton_poly"));

        gridLayout->addWidget(radioButton_poly, 6, 0, 1, 1);

        radioButton_blur = new QRadioButton(verticalLayoutWidget);
        radioButton_blur->setObjectName(QString::fromUtf8("radioButton_blur"));
        radioButton_blur->setChecked(true);

        gridLayout->addWidget(radioButton_blur, 2, 0, 1, 1);

        doubleSpinBox_gauSigma = new QDoubleSpinBox(verticalLayoutWidget);
        doubleSpinBox_gauSigma->setObjectName(QString::fromUtf8("doubleSpinBox_gauSigma"));
        doubleSpinBox_gauSigma->setMinimum(10);
        doubleSpinBox_gauSigma->setMaximum(30);
        doubleSpinBox_gauSigma->setSingleStep(2.5);
        doubleSpinBox_gauSigma->setValue(20);

        gridLayout->addWidget(doubleSpinBox_gauSigma, 2, 2, 1, 1);

        spinBox_polyAcy = new QSpinBox(verticalLayoutWidget);
        spinBox_polyAcy->setObjectName(QString::fromUtf8("spinBox_polyAcy"));
        spinBox_polyAcy->setMinimum(5);
        spinBox_polyAcy->setMaximum(9);
        spinBox_polyAcy->setSingleStep(2);

        gridLayout->addWidget(spinBox_polyAcy, 6, 1, 1, 2);

        spinBox_egThd = new QSpinBox(verticalLayoutWidget);
        spinBox_egThd->setObjectName(QString::fromUtf8("spinBox_egThd"));
        spinBox_egThd->setMaximum(255);
        spinBox_egThd->setSingleStep(5);
        spinBox_egThd->setValue(15);

        gridLayout->addWidget(spinBox_egThd, 3, 1, 1, 1);

        doubleSpinBox_egGauSigma = new QDoubleSpinBox(verticalLayoutWidget);
        doubleSpinBox_egGauSigma->setObjectName(QString::fromUtf8("doubleSpinBox_egGauSigma"));
        doubleSpinBox_egGauSigma->setMaximum(20);
        doubleSpinBox_egGauSigma->setSingleStep(2.5);

        gridLayout->addWidget(doubleSpinBox_egGauSigma, 3, 2, 1, 1);

        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 480, 1021, 181));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_sensitivity = new QLabel(gridLayoutWidget);
        label_sensitivity->setObjectName(QString::fromUtf8("label_sensitivity"));

        gridLayout_2->addWidget(label_sensitivity, 1, 1, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 4, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 3, 0, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 1, 0, 1, 1);

        label_bgThresh = new QLabel(gridLayoutWidget);
        label_bgThresh->setObjectName(QString::fromUtf8("label_bgThresh"));

        gridLayout_2->addWidget(label_bgThresh, 2, 1, 1, 1);

        label_lnRate = new QLabel(gridLayoutWidget);
        label_lnRate->setObjectName(QString::fromUtf8("label_lnRate"));

        gridLayout_2->addWidget(label_lnRate, 3, 1, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 2, 0, 1, 1);

        label_noiseVar = new QLabel(gridLayoutWidget);
        label_noiseVar->setObjectName(QString::fromUtf8("label_noiseVar"));

        gridLayout_2->addWidget(label_noiseVar, 4, 1, 1, 1);

        label_bgModel = new QLabel(gridLayoutWidget);
        label_bgModel->setObjectName(QString::fromUtf8("label_bgModel"));

        gridLayout_2->addWidget(label_bgModel, 0, 0, 1, 2, Qt::AlignHCenter);

        textBrowser_runMessage = new QTextBrowser(gridLayoutWidget);
        textBrowser_runMessage->setObjectName(QString::fromUtf8("textBrowser_runMessage"));
        textBrowser_runMessage->setEnabled(true);

        gridLayout_2->addWidget(textBrowser_runMessage, 0, 2, 5, 1);

        checkBox_Erosion = new QCheckBox(gridLayoutWidget);
        checkBox_Erosion->setObjectName(QString::fromUtf8("checkBox_Erosion"));

        gridLayout_2->addWidget(checkBox_Erosion, 0, 4, 1, 1);

        spinBox_EroSize = new QSpinBox(gridLayoutWidget);
        spinBox_EroSize->setObjectName(QString::fromUtf8("spinBox_EroSize"));
        spinBox_EroSize->setMinimum(1);
        spinBox_EroSize->setMaximum(21);
        spinBox_EroSize->setSingleStep(2);
        spinBox_EroSize->setValue(3);

        gridLayout_2->addWidget(spinBox_EroSize, 0, 6, 1, 1);

        comboBox_EroType = new QComboBox(gridLayoutWidget);
        comboBox_EroType->setObjectName(QString::fromUtf8("comboBox_EroType"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBox_EroType->sizePolicy().hasHeightForWidth());
        comboBox_EroType->setSizePolicy(sizePolicy3);
        comboBox_EroType->setMaximumSize(QSize(100, 27));
        comboBox_EroType->setEditable(true);
        comboBox_EroType->setMaxVisibleItems(3);

        gridLayout_2->addWidget(comboBox_EroType, 0, 5, 1, 1);

        checkBox_dilate = new QCheckBox(gridLayoutWidget);
        checkBox_dilate->setObjectName(QString::fromUtf8("checkBox_dilate"));

        gridLayout_2->addWidget(checkBox_dilate, 1, 4, 1, 1);

        comboBox_DilType = new QComboBox(gridLayoutWidget);
        comboBox_DilType->setObjectName(QString::fromUtf8("comboBox_DilType"));
        comboBox_DilType->setEditable(true);

        gridLayout_2->addWidget(comboBox_DilType, 1, 5, 1, 1);

        spinBox_DilSize = new QSpinBox(gridLayoutWidget);
        spinBox_DilSize->setObjectName(QString::fromUtf8("spinBox_DilSize"));
        spinBox_DilSize->setMinimum(1);
        spinBox_DilSize->setMaximum(21);
        spinBox_DilSize->setSingleStep(2);
        spinBox_DilSize->setValue(3);

        gridLayout_2->addWidget(spinBox_DilSize, 1, 6, 1, 1);

        checkBox_morphClose = new QCheckBox(gridLayoutWidget);
        checkBox_morphClose->setObjectName(QString::fromUtf8("checkBox_morphClose"));
        checkBox_morphClose->setChecked(true);

        gridLayout_2->addWidget(checkBox_morphClose, 2, 4, 1, 1);

        comboBox_mclType = new QComboBox(gridLayoutWidget);
        comboBox_mclType->setObjectName(QString::fromUtf8("comboBox_mclType"));
        comboBox_mclType->setEditable(true);

        gridLayout_2->addWidget(comboBox_mclType, 2, 5, 1, 1);

        spinBox_mclSize = new QSpinBox(gridLayoutWidget);
        spinBox_mclSize->setObjectName(QString::fromUtf8("spinBox_mclSize"));
        spinBox_mclSize->setMinimum(1);
        spinBox_mclSize->setMaximum(21);
        spinBox_mclSize->setSingleStep(2);
        spinBox_mclSize->setValue(7);

        gridLayout_2->addWidget(spinBox_mclSize, 2, 6, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1282, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionOpen_Background);
        menuFile->addAction(actionLIVE);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuEdit->addAction(actionOCV_MD);
        menuEdit->addAction(actionMix_Gaussian_MD);
        menuEdit->addAction(actionFull_Screen);

        retranslateUi(MainWindow);

        comboBox_EroType->setCurrentIndex(0);


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
        actionOCV_MD->setText(QApplication::translate("MainWindow", "OCV MD", 0, QApplication::UnicodeUTF8));
        actionMix_Gaussian_MD->setText(QApplication::translate("MainWindow", "Mix Gaussian MD", 0, QApplication::UnicodeUTF8));
        actionFull_Screen->setText(QApplication::translate("MainWindow", "Full Screen", 0, QApplication::UnicodeUTF8));
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
        checkBox_record->setText(QApplication::translate("MainWindow", "record", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_debug->setText(QString());
        checkBox_blackOriginal->setText(QApplication::translate("MainWindow", "black", 0, QApplication::UnicodeUTF8));
        checkBox_shadow->setText(QApplication::translate("MainWindow", "shadowDet", 0, QApplication::UnicodeUTF8));
        checkBox_rect->setText(QApplication::translate("MainWindow", "rectangle", 0, QApplication::UnicodeUTF8));
        radioButton_orig->setText(QApplication::translate("MainWindow", "original", 0, QApplication::UnicodeUTF8));
        radioButton_back->setText(QApplication::translate("MainWindow", "background", 0, QApplication::UnicodeUTF8));
        radioButton_fore->setText(QApplication::translate("MainWindow", "foreground", 0, QApplication::UnicodeUTF8));
        radioButton_color->setText(QApplication::translate("MainWindow", "color", 0, QApplication::UnicodeUTF8));
        radioButton_grey->setText(QApplication::translate("MainWindow", "grey", 0, QApplication::UnicodeUTF8));
        radioButton_debug->setText(QApplication::translate("MainWindow", "DEBUG", 0, QApplication::UnicodeUTF8));
        checkBox_greyROI->setText(QApplication::translate("MainWindow", "grey roi", 0, QApplication::UnicodeUTF8));
        radioButton_mosaic->setText(QApplication::translate("MainWindow", "mosaic", 0, QApplication::UnicodeUTF8));
        checkBox_shape->setText(QApplication::translate("MainWindow", "shape", 0, QApplication::UnicodeUTF8));
        radioButton_black->setText(QApplication::translate("MainWindow", "black", 0, QApplication::UnicodeUTF8));
        radioButton_default->setText(QApplication::translate("MainWindow", "default", 0, QApplication::UnicodeUTF8));
        radioButton_silhouette->setText(QApplication::translate("MainWindow", "silhouette", 0, QApplication::UnicodeUTF8));
        radioButton_edge->setText(QApplication::translate("MainWindow", "edge", 0, QApplication::UnicodeUTF8));
        checkBox_privacy->setText(QApplication::translate("MainWindow", "anonymous mode", 0, QApplication::UnicodeUTF8));
        radioButton_poly->setText(QApplication::translate("MainWindow", "poly", 0, QApplication::UnicodeUTF8));
        radioButton_blur->setText(QApplication::translate("MainWindow", "blur", 0, QApplication::UnicodeUTF8));
        label_sensitivity->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "noise vriance", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "learning rate", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "sensitivity", 0, QApplication::UnicodeUTF8));
        label_bgThresh->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_lnRate->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "bg threshold", 0, QApplication::UnicodeUTF8));
        label_noiseVar->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_bgModel->setText(QApplication::translate("MainWindow", "Background Model", 0, QApplication::UnicodeUTF8));
        checkBox_Erosion->setText(QApplication::translate("MainWindow", "erosion", 0, QApplication::UnicodeUTF8));
        comboBox_EroType->clear();
        comboBox_EroType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "ellipse", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "rectangle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "cross", 0, QApplication::UnicodeUTF8)
        );
        checkBox_dilate->setText(QApplication::translate("MainWindow", "dilate", 0, QApplication::UnicodeUTF8));
        comboBox_DilType->clear();
        comboBox_DilType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "ellipse", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "rectangle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "cross", 0, QApplication::UnicodeUTF8)
        );
        checkBox_morphClose->setText(QApplication::translate("MainWindow", "morph close", 0, QApplication::UnicodeUTF8));
        comboBox_mclType->clear();
        comboBox_mclType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "ellipse", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "rectangle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "cross", 0, QApplication::UnicodeUTF8)
        );
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
