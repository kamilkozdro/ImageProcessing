#include "CImageHandler.h"

CImageHandler::CImageHandler()
{
    keptFrame1Number = 0;
    keptFrame2Number = 0;
}

CImageHandler::~CImageHandler() {}

void CImageHandler::removeFilter(unsigned int index)
{
    try {
        if (index >= filterList.size()) {
            throw std::invalid_argument("Index out of range");
        }
        filterList.remove(index);

    } catch (std::exception &e) {
        std::cerr << "CImageHandler::removeFilter():" << e.what() << std::endl;
        return;
    }
}

void CImageHandler::updateObject()
{
    try {
        if (frame.empty())
            throw std::logic_error("Empty frame");
        if (cam.isOpened())
            cam >> frame;

        if (keptFrame1Number == 0)
            frame.copyTo(keptFrame1);
        if (keptFrame2Number == 0)
            frame.copyTo(keptFrame2);

        if (keptFrame1Number != 0 || keptFrame2Number != 0) {
            frame.copyTo(filteredFrame);
            for (int i = 0; i < filterList.size(); ++i) {
                useFilter(filteredFrame, filteredFrame, filterList.at(i));
                if (keptFrame1Number == i + 1)
                    filteredFrame.copyTo(keptFrame1);
                else if (keptFrame2Number == i + 1)
                    filteredFrame.copyTo(keptFrame2);
            }
        }
    } catch (std::exception &e) {
        std::cerr << "CImageHandler::updateObject():" << e.what() << std::endl;
        return;
    }
}

void CImageHandler::useFilter(cv::Mat &src, cv::Mat &dest, CFilter *filter)
{
    // DODAC WPROWADZANIE PARAMETROW PO NAZWIE?
    try {
        switch (filter->getType()) {
        case CFilter::filterType::Blur:
            cv::blur(src,
                     dest,
                     cv::Size(filter->getParameterValue(0), filter->getParameterValue(0)));
            break;

        case CFilter::filterType::Sobel:
            cv::Sobel(src,
                      dest,
                      -1,
                      filter->getParameterValue(0),
                      filter->getParameterValue(1),
                      filter->getParameterValue(2));
            break;

        case CFilter::filterType::Dilate:
            cv::dilate(src, dest, cv::Mat(), cv::Point(-1, -1), filter->getParameterValue(0));
            break;

        case CFilter::filterType::Erode:
            cv::erode(src, dest, cv::Mat(), cv::Point(-1, -1), filter->getParameterValue(0));
            break;

        case CFilter::filterType::Gaussian:
            cv::GaussianBlur(src,
                             dest,
                             cv::Size(filter->getParameterValue(0), filter->getParameterValue(0)),
                             filter->getParameterValue(1),
                             filter->getParameterValue(2));
            break;

        case CFilter::filterType::Laplacian:
            cv::Laplacian(src, dest, -1, filter->getParameterValue(0));
            break;

        case CFilter::filterType::Medianblur:
            cv::medianBlur(src, dest, filter->getParameterValue(0));
            break;

        default:
            throw std::invalid_argument("Uknown type of filter");
            break;
        }
    } catch (std::exception &e) {
        std::cerr << "CImageHandler::useFilter()" << e.what() << std::endl;
        return;
    }
}
