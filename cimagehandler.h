#ifndef CImageHandler_H
#define CImageHandler_H

#include <QDebug>
#include <QMessageBox>
#include "cfilter.h"
#include "opencv2/opencv.hpp"

class CImageHandler
{
public:
    CImageHandler();
    ~CImageHandler();

    void addFilter(CFilter *newFilter) { filterList.append(newFilter); };
    void removeFilter(unsigned int index);
    void processImage(cv::Mat& src, cv::Mat& dst, int lastFilterIndex = -1);

private:
    QList<CFilter*> filterList;

};

#endif // CImageHandler_H
