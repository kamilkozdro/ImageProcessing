#include "cimagefilesource.h"

CImageFileSource::CImageFileSource()
    :imageLoaded(false)
{

}

void CImageFileSource::open(QString arg)
{
    image = cv::imread(arg.toStdString());
    if (image.data == NULL)
    {
        showMessageBox("Cannot load image", "Warning", QMessageBox::Icon::Warning);
        imageLoaded = false;
    }
    else
    {
        imageLoaded = true;
    }
}

void CImageFileSource::close()
{
    image.release();
    imageLoaded = false;
}

cv::Mat& CImageFileSource::getImage()
{
    return image;
}
