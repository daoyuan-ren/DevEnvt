#include "virtualcamera.h"

VirtualCamera::VirtualCamera()
{
    camID       = -1;
    posX        = -1;
    posY        = -1;
    camWidth    = 0;
    camHeight   = 0;
}

VirtualCamera::VirtualCamera(int id, int width, int height){
    camID       = id;
    posX        = -1;
    posY        = -1;
    camWidth    = width;
    camHeight   = height;
}

VirtualCamera::VirtualCamera(int x, int y, int width, int height){
    camID       = -1;
    posX        = x;
    posX        = y;
    camWidth    = width;
    camHeight   = height;
}

VirtualCamera::VirtualCamera(int id, int x, int y, int width, int height){
    camID       = id;
    posX        = x;
    posX        = y;
    camWidth    = width;
    camHeight   = height;
}

void VirtualCamera::setX(int x){
    posX = x;
}

void VirtualCamera::setY(int y){
    posY = y;
}

void VirtualCamera::setCamWidth(int width){
    camWidth = width;
}

void VirtualCamera::setCamHeight(int height){
    camHeight = height;
}

void VirtualCamera::setCamera(int id, int width, int height){
    camID       = id;
    posX        = -1;
    posY        = -1;
    camWidth    = width;
    camHeight   = height;
}

void VirtualCamera::setID(int id){
    camID = id;
}

void VirtualCamera::remove(){
    camID       = -1;
    posX        = -1;
    posY        = -1;
    camWidth    = 0;
    camHeight   = 0;
}

int VirtualCamera::x(){
    return posX;
}

int VirtualCamera::y(){
    return posY;
}

int VirtualCamera::width(){
    return camWidth;
}

int VirtualCamera::height(){
    return camHeight;
}

int VirtualCamera::id(){
    return camID;
}

void VirtualCamera::getRegion(){
    if(posX == -1 && posY == -1)
        camRegion.setRect(0, 0, 0, 0);
    else
        camRegion.setRect(posX - camWidth/4, posY - camHeight/4, camWidth/2, camHeight/2);
}

QRect VirtualCamera::region(){
    getRegion();
    return camRegion;
}
