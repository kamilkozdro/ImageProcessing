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
    inline void setKeptFrame1(int filterNumber) { keptFrame1Number = filterNumber; }
    inline void setKeptFrame2(int filterNumber) { keptFrame2Number = filterNumber; }
    inline cv::Mat getFrame1() { return keptFrame1; }
    inline cv::Mat getFrame2() { return keptFrame2; }
    void updateObject();


    inline void setFrame(cv::Mat& newFrame){frame = newFrame;};

private:
    cv::Mat frame, filteredFrame, keptFrame1, keptFrame2;
    int keptFrame1Number, keptFrame2Number;
    QList<CFilter *> filterList;

    void useFilter(cv::Mat &src, cv::Mat &dest, CFilter *filter);

};

#endif // CImageHandler_H
