#include "cimagecamerasource.h"

CImageCameraSource::CImageCameraSource() {}

void CImageCameraSource::open(QString arg)
{
    bool convertResult = false;
    int camId = arg.toInt(&convertResult);

    if (!convertResult) {
        showMessageBox("Wrong camera ID", "Warning", QMessageBox::Icon::Warning);
        return;
    }

    if (!camera.open(camId)) {
        showMessageBox("Cannot open camera", "Warning", QMessageBox::Icon::Warning);
        return;
    }
}

void CImageCameraSource::close()
{
    camera.release();
    image.release();
}

cv::Mat &CImageCameraSource::getImage()
{
    if (isOpen())
        camera >> image;

    return image;
}
