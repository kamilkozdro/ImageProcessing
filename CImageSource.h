#ifndef CIMAGESOURCE_H
#define CIMAGESOURCE_H


#include "opencv2/opencv.hpp"

class CImageSource
{
public:
    virtual void open() = 0;
    virtual void close() = 0;
    virtual cv::Mat& getImage() = 0;

private:


protected:


};

#endif // CIMAGESOURCE_H


