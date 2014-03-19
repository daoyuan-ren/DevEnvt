#include "camlabel.h"

CamLabel::CamLabel(QWidget *parent) :
    QLabel(parent)
{
    vcam = NULL;
}

void CamLabel::setCamera(VirtualCamera *vcam){
    this->vcam = vcam;
}

void CamLabel::mousePressEvent(QMouseEvent *ev){
    /*QString x = QString::number(ev->x());
    QString y = QString::number(ev->y());

    if(ev->button() == Qt::LeftButton || vcam != NULL){
        int camWidth = vcam->width() / 3;
        int camHeight = vcam->height() / 3;
        vcam->setX(ev->x());
        vcam->setY(ev->y());
        QImage image = this->pixmap()->toImage().scaled(width(), height());
        if(image.isNull())
            return;

        QPainter painter(&image);
        QPen pen(Qt::gray);
        pen.setWidth(2);
        pen.setCapStyle(Qt::RoundCap);
        QRect p(ev->x() - camWidth/2, ev->y() - camHeight/2, camWidth, camHeight);
        painter.setPen(pen);
        painter.drawRect(p);
        this->setPixmap(QPixmap::fromImage(image));
    }*/
}

void CamLabel::mouseDoubleClickEvent(QMouseEvent *ev){
    QString x = QString::number(ev->x());
    QString y = QString::number(ev->y());

    if(ev->button() == Qt::LeftButton && vcam != NULL){
        int camWidth = vcam->width() / 2;
        int camHeight = vcam->height() / 2;
        if(vcam->x() >= 0 && vcam->y() >= 0 && vcam->region().contains(ev->x(), ev->y())){
            vcam->remove();
            return;
        }
        vcam->setX(ev->x());
        vcam->setY(ev->y());
        QImage image = this->pixmap()->toImage().scaled(width(), height());
        if(image.isNull())
            return;


        QPainter painter(&image);
        QPen pen(Qt::gray);
        pen.setWidth(2);
        pen.setCapStyle(Qt::RoundCap);
        QRect p(ev->x() - camWidth/2, ev->y() - camHeight/2, camWidth, camHeight);
        painter.setPen(pen);
        painter.drawRect(p);
        this->setPixmap(QPixmap::fromImage(image));
    }
}

void CamLabel::setImage(QImage image){
    if(image.isNull())
        return;

    QImage scaledImage = image.scaled(width(), height());
    if(vcam->x() >= 0 && vcam->y() >= 0){
        QPainter painter(&scaledImage);
        QPen pen(Qt::gray);
        pen.setWidth(2);
        pen.setCapStyle(Qt::RoundCap);
        QRect p(vcam->x() - vcam->width()/4, vcam->y() - vcam->height()/4, vcam->width()/2, vcam->height()/2);
        painter.setPen(pen);
        painter.drawRect(p);
    }
    this->setPixmap(QPixmap::fromImage(scaledImage));
}
