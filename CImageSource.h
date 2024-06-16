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

    static void scaleImage(cv::Mat &src, cv::Mat &dst, int maxScale)
    {
        if(src.rows <= maxScale && src.cols <= maxScale)
            return;

        float scaleFactor = 0.0;
        if(src.rows > src.cols)
            scaleFactor = (float)maxScale / src.rows;
        else
            scaleFactor = (float)maxScale / src.cols;

        cv::resize(src, dst, cv::Size(), scaleFactor, scaleFactor);
    }
};

#endif // CIMAGESOURCE_H
