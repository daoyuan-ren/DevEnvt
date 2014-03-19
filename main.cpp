#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if(argc == 3){
        QString imageFileName(argv[1]);
        if(!imageFileName.isEmpty())
            w.setBackground(new QImage(imageFileName));

        QString videoFileName(argv[2]);
        w.process(videoFileName, false);

    } else if (argc == 2){
        QString videoFileName(argv[1]);
        w.process(videoFileName, false);
    }
    
    return a.exec();
}
