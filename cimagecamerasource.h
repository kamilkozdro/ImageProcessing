#ifndef CIMAGECAMERASOURCE_H
#define CIMAGECAMERASOURCE_H

#include "CImageSource.h"
#include "CMessageBox.h"

class CImageCameraSource : public CImageSource, CMessageBox
{
public:
    CImageCameraSource();
    ~CImageCameraSource() override{};
    void open(QString arg) override;
    inline bool isOpen() override { return camera.isOpened(); };
    void close() override;
    cv::Mat &getImage() override;

protected:
    cv::VideoCapture camera;
};

#endif // CIMAGECAMERASOURCE_H
