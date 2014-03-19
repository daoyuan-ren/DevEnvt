#ifndef CAMLABEL_H
#define CAMLABEL_H

#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>

#include <iostream>
#include "virtualcamera.h"

using namespace std;

class CamLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CamLabel(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *ev);

    void setCamera(VirtualCamera* vcam);
    void setImage(QImage image);

private:

    VirtualCamera* vcam;

signals:
    
public slots:
    
};

#endif // CAMLABEL_H
