#ifndef CIMAGEFILESOURCE_H
#define CIMAGEFILESOURCE_H

#include <QFileDialog>
#include <QString>
#include "CImageSource.h"
#include "CMessageBox.h"

class CImageFileSource : public CImageSource, CMessageBox
{
public:
    CImageFileSource();
    ~CImageFileSource() override{};

    void open(QString arg) override;
    inline bool isOpen() override { return imageLoaded; };
    void close() override;
    cv::Mat &getImage() override;

protected:
    bool imageLoaded;
};

#endif // CIMAGEFILESOURCE_H
