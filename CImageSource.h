#ifndef CIMAGESOURCE_H
#define CIMAGESOURCE_H

#include <QString>
#include "opencv2/opencv.hpp"

class CImageSource
{
public:
    virtual ~CImageSource(){};
    virtual void open(QString arg) = 0;
    virtual bool isOpen() = 0;
    virtual void close() = 0;
    virtual cv::Mat &getImage() = 0;

private:
protected:
    cv::Mat image;
};

#endif // CIMAGESOURCE_H
