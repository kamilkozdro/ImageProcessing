#ifndef CIMAGEFILESOURCE_H
#define CIMAGEFILESOURCE_H

#include "CImageSource.h"
#include "CMessageBox.h"

class CImageFileSource : public CImageSource, CMessageBox
{
public:
    CImageFileSource();

    void open(QString arg);
    inline bool isOpen(){return imageLoaded;};
    void close();
    cv::Mat& getImage();

protected:
    bool imageLoaded;
};

#endif // CIMAGEFILESOURCE_H
