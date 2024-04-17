#ifndef CIMAGECAMERASOURCE_H
#define CIMAGECAMERASOURCE_H

#include "CImageSource.h"
#include "CMessageBox.h"

class CImageCameraSource : public CImageSource, CMessageBox
{
public:
    CImageCameraSource();

    void open(QString arg);
    inline bool isOpen(){return camera.isOpened();};
    void close();
    cv::Mat & getImage();

protected:
    cv::VideoCapture camera;
};

#endif // CIMAGECAMERASOURCE_H
