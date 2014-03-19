#-------------------------------------------------
#
# Project created by QtCreator 2013-12-17T16:24:43
#
#-------------------------------------------------

QT       += core gui

TARGET = DevEntv
TEMPLATE = app

CV11_INCLUDE = /usr/local/include/opencv
CV11_LIB = /usr/local/lib
CV22_INCLUDE = /usr/local/include/OpenCV2
CV22_LIB = /usr/local/lib/OpenCV2

SOURCES += main.cpp\
        mainwindow.cpp \
    playthread.cpp \
    blober.cpp \
    framemanager.cpp \
    package_bgs/lb/LBMixtureOfGaussians.cpp \
    package_bgs/lb/BGModelMog.cpp \
    package_bgs/lb/BGModel.cpp \
    roidialog.cpp \
    camlabel.cpp \
    virtualcamera.cpp

HEADERS  += mainwindow.h \
    playthread.h \
    blober.h \
    framemanager.h \
    package_bgs/lb/LBMixtureOfGaussians.h \
    package_bgs/lb/BGModelMog.h \
    package_bgs/lb/BGModel.h \
    roidialog.h \
    camlabel.h \
    virtualcamera.h

FORMS    += mainwindow.ui \
    roidialog.ui

contains(cv,2){
	message(build with opencv 2)
	DEFINES += OPEN_CV_22
	INCLUDEPATH += $$CV22_INCLUDE/core/include/opencv2/core \
				   $$CV22_INCLUDE/highgui/include/opencv2/highgui \
				   $$CV22_INCLUDE/imgproc/include/opencv2/imgproc \
				   $$CV22_INCLUDE/core/include	\
				   $$CV22_INCLUDE/imgproc/include
	LIBS += -L$$CV22_LIB
	LIBS += -lopencv_highgui220 -lopencv_core220 -lopencv_imgproc220 \
		-lopencv_features2d220 -lopencv_flann220 -lopencv_objdetect220 -lopencv_ml220 -lopencv_video220  -lopencv_legacy220 -lopencv_contrib220 -lopencv_calib3d220 -pthread
} else{
	message(build with opencv 1.1)
	DEFINES -= OPEN_CV_22
	INCLUDEPATH += $$CV11_INCLUDE/cv/include $$CV11_INCLUDE/otherlibs/highgui $$CV11_INCLUDE/cxcore/include
	LIBS += -L$$CV11_LIB
	LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_features2d -lopencv_flann -lopencv_objdetect -lopencv_ml -lopencv_video  -lopencv_legacy -lopencv_contrib -lopencv_calib3d -pthread
}
