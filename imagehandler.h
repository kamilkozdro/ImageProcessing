#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "opencv2/opencv.hpp"
#include "cfilter.h"
#include <QDebug>
#include <QMessageBox>

class ImageHandler
{
public:
    ImageHandler();
    ~ImageHandler();

    int openCam(int camID);
    inline void releaseCam(){cam.release();}
    inline bool isCamOpened(){return cam.isOpened();}
    void openImage(QString filePath);
    void addFilter(CFilter* newFilter){filterList.append(newFilter);};
    void removeFilter(unsigned int index);
    inline void setKeptFrame1(int filterNumber){keptFrame1Number = filterNumber;}
    inline void setKeptFrame2(int filterNumber){keptFrame2Number = filterNumber;}
    inline cv::Mat getFrame1(){return keptFrame1;}
    inline cv::Mat getFrame2(){return keptFrame2;}
    void updateObject();
    bool isImageLoaded(){return imageLoaded;};

private:
    cv::VideoCapture cam;
    bool imageLoaded;
    cv::Mat frame, filteredFrame, keptFrame1, keptFrame2;
    int keptFrame1Number ,keptFrame2Number;
    QList<CFilter*> filterList;

    void useFilter(cv::Mat &src, cv::Mat &dest, CFilter *filter);
    void showMessageBox(QString text, QString title = "",
                        QMessageBox::Icon icon = QMessageBox::Icon::NoIcon);
};

#endif // IMAGEHANDLER_H
