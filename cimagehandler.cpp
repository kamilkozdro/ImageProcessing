#include "CImageHandler.h"

CImageHandler::CImageHandler()
{
}

CImageHandler::~CImageHandler() {}

void CImageHandler::removeFilter(unsigned int index)
{
    try
    {
        if (index >= filterList.size())
        {
            throw std::invalid_argument("Index out of range");
        }
        filterList.remove(index);

    }
    catch (std::exception &e)
    {
        std::cerr << "CImageHandler::removeFilter():" << e.what() << std::endl;
        return;
    }
}

void CImageHandler::processImage(cv::Mat& src, cv::Mat& dst, int lastFilterIndex)
{
    if(lastFilterIndex  < 0 || lastFilterIndex > filterList.count())
        lastFilterIndex = filterList.count();

    for (int i = 0; i < lastFilterIndex; ++i)
    {
        filterList.at(i)->useFilter(src, dst);
    }
}
