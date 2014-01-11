/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Jan 11 14:22:16 2014
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
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionQuit;
    QAction *actionOpen_Background;
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
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_debug;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox_rect;
    QRadioButton *radioButton_orig;
    QRadioButton *radioButton_grey;
    QRadioButton *radioButton_back;
    QRadioButton *radioButton_fore;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkBox_privacy;
    QRadioButton *radioButton_black;
    QRadioButton *radioButton_blur;
    QRadioButton *radioButton_edge;
    QRadioButton *radioButton_border;
    QRadioButton *radioButton_default;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1103, 518);
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

        pushButton_live = new QPushButton(horizontalLayoutWidget);
        pushButton_live->setObjectName(QString::fromUtf8("pushButton_live"));

        horizontalLayout->addWidget(pushButton_live);

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
        label->setStyleSheet(QString::fromUtf8("border-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));
        label->setScaledContents(true);

        horizontalLayout_2->addWidget(label);

        label_debug = new QLabel(horizontalLayoutWidget_2);
        label_debug->setObjectName(QString::fromUtf8("label_debug"));
        label_debug->setScaledContents(true);

        horizontalLayout_2->addWidget(label_debug);

        horizontalLayoutWidget_3 = new QWidget(centralWidget);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(0, 0, 1101, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

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

        radioButton_grey = new QRadioButton(horizontalLayoutWidget_3);
        radioButton_grey->setObjectName(QString::fromUtf8("radioButton_grey"));
        radioButton_grey->setChecked(true);

        horizontalLayout_3->addWidget(radioButton_grey);

        radioButton_back = new QRadioButton(horizontalLayoutWidget_3);
        radioButton_back->setObjectName(QString::fromUtf8("radioButton_back"));

        horizontalLayout_3->addWidget(radioButton_back);

        radioButton_fore = new QRadioButton(horizontalLayoutWidget_3);
        radioButton_fore->setObjectName(QString::fromUtf8("radioButton_fore"));
        radioButton_fore->setChecked(false);

        horizontalLayout_3->addWidget(radioButton_fore);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(1020, 30, 153, 391));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        checkBox_privacy = new QCheckBox(verticalLayoutWidget);
        checkBox_privacy->setObjectName(QString::fromUtf8("checkBox_privacy"));
        checkBox_privacy->setChecked(true);

        verticalLayout->addWidget(checkBox_privacy);

        radioButton_black = new QRadioButton(verticalLayoutWidget);
        radioButton_black->setObjectName(QString::fromUtf8("radioButton_black"));
        radioButton_black->setChecked(false);

        verticalLayout->addWidget(radioButton_black);

        radioButton_blur = new QRadioButton(verticalLayoutWidget);
        radioButton_blur->setObjectName(QString::fromUtf8("radioButton_blur"));

        verticalLayout->addWidget(radioButton_blur);

        radioButton_edge = new QRadioButton(verticalLayoutWidget);
        radioButton_edge->setObjectName(QString::fromUtf8("radioButton_edge"));

        verticalLayout->addWidget(radioButton_edge);

        radioButton_border = new QRadioButton(verticalLayoutWidget);
        radioButton_border->setObjectName(QString::fromUtf8("radioButton_border"));

        verticalLayout->addWidget(radioButton_border);

        radioButton_default = new QRadioButton(verticalLayoutWidget);
        radioButton_default->setObjectName(QString::fromUtf8("radioButton_default"));
        radioButton_default->setChecked(true);

        verticalLayout->addWidget(radioButton_default);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1103, 27));
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
        label->setText(QString());
        label_debug->setText(QString());
        checkBox_rect->setText(QApplication::translate("MainWindow", "rectangle", 0, QApplication::UnicodeUTF8));
        radioButton_orig->setText(QApplication::translate("MainWindow", "original", 0, QApplication::UnicodeUTF8));
        radioButton_grey->setText(QApplication::translate("MainWindow", "grey", 0, QApplication::UnicodeUTF8));
        radioButton_back->setText(QApplication::translate("MainWindow", "background", 0, QApplication::UnicodeUTF8));
        radioButton_fore->setText(QApplication::translate("MainWindow", "foreground", 0, QApplication::UnicodeUTF8));
        checkBox_privacy->setText(QApplication::translate("MainWindow", "privacy", 0, QApplication::UnicodeUTF8));
        radioButton_black->setText(QApplication::translate("MainWindow", "black", 0, QApplication::UnicodeUTF8));
        radioButton_blur->setText(QApplication::translate("MainWindow", "blur", 0, QApplication::UnicodeUTF8));
        radioButton_edge->setText(QApplication::translate("MainWindow", "edge", 0, QApplication::UnicodeUTF8));
        radioButton_border->setText(QApplication::translate("MainWindow", "border", 0, QApplication::UnicodeUTF8));
        radioButton_default->setText(QApplication::translate("MainWindow", "default", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
