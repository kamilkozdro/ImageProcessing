#include "cimagefilesource.h"

CImageFileSource::CImageFileSource()
    :imageLoaded(false)
{

}

void CImageFileSource::open(QString arg)
{

    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    "Open Image",
                                                    "",
                                                    "Image Files (*.png *.jpg *.bmp)");

    if (fileName.isEmpty())
    {
        imageLoaded = false;
        return;
    }

    image = cv::imread(fileName.toStdString());

    if (image.data == NULL)
    {
        showMessageBox("Cannot load image", "Warning", QMessageBox::Icon::Warning);
        imageLoaded = false;
        return;
    }

    imageLoaded = true;
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
