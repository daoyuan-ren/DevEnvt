#ifndef VIRTUALCAMERA_H
#define VIRTUALCAMERA_H

#include <QRect>
#include <QPixmap>

class VirtualCamera
{
public:
    VirtualCamera();
    VirtualCamera(int id, int width, int height);
    VirtualCamera(int x, int y, int width, int height);
    VirtualCamera(int id, int x, int y, int width, int height);

    void setX(int x);
    void setY(int y);
    void setID(int id);
    void setCamWidth(int width);
    void setCamHeight(int height);
    void setCamera(int id, int width, int height);
    void remove();

    int x();
    int y();
    int id();
    int width();
    int height();

    QRect region();


private:
    int camID;
    int posX;
    int posY;
    int camWidth;
    int camHeight;
    QRect camRegion;

    void getRegion();
};

#endif // VIRTUALCAMERA_H
