#include "imagehandler.h"

ImageHandler::ImageHandler()
{
    keptFrame1Number = 0;
    keptFrame2Number = 0;
}

ImageHandler::~ImageHandler()
{

}

int ImageHandler::openCam(int camID)
{
    if(!cam.open(camID))
    {
        showMessageBox("Cannot open camera", "Warning", QMessageBox::Icon::Warning);
        return 0;
    }

    imageLoaded = false;

    return 1;
}

void ImageHandler::openImage(QString filePath)
{
    frame = cv::imread(filePath.toStdString());

    if(frame.data == NULL)
    {
        showMessageBox("Cannot load image", "Warning", QMessageBox::Icon::Warning);
        return;
    }

    imageLoaded = true;
}

void ImageHandler::removeFilter(unsigned int index)
{
    try
    {
        if(index >= filterList.size())
        {
            throw std::invalid_argument("Index out of range");
        }
        filterList.remove(index);

    }
    catch(std::exception &e)
    {
        std::cerr << "ImageHandler::removeFilter():" << e.what() << std::endl;
        return;
    }
}

void ImageHandler::updateObject()
{
    try
    {
        if(frame.empty())
            throw std::logic_error("Empty frame");
        if(cam.isOpened())
            cam >> frame;

        if(keptFrame1Number == 0)
            frame.copyTo(keptFrame1);
        if(keptFrame2Number == 0)
            frame.copyTo(keptFrame2);

        if(keptFrame1Number != 0 || keptFrame2Number != 0)
        {
            frame.copyTo(filteredFrame);
            for(int i = 0; i < filterList.size(); ++i)
            {
                useFilter(filteredFrame, filteredFrame, filterList.at(i));
                if(keptFrame1Number == i+1)
                    filteredFrame.copyTo(keptFrame1);
                else if(keptFrame2Number == i+1)
                    filteredFrame.copyTo(keptFrame2);
            }
        }
    }
    catch(std::exception &e)
    {
        std::cerr << "ImageHandler::updateObject():" << e.what() << std::endl;
        return;
    }


}

void ImageHandler::useFilter(cv::Mat &src, cv::Mat &dest, CFilter *filter)
{
    // DODAC WPROWADZANIE PARAMETROW PO NAZWIE?
    try
    {
        switch(filter->getType())
        {
        case CFilter::filterType::Blur:
            cv::blur(src, dest, cv::Size(filter->getParameterValue(0),
                                         filter->getParameterValue(0)));
        break;

        case CFilter::filterType::Sobel:
            cv::Sobel(src, dest, -1,
                      filter->getParameterValue(0),
                      filter->getParameterValue(1),
                      filter->getParameterValue(2));
            break;

        case CFilter::filterType::Dilate:
            cv::dilate(src, dest, cv::Mat(), cv::Point(-1,-1),
                       filter->getParameterValue(0));
            break;

        case CFilter::filterType::Erode:
            cv::erode(src, dest, cv::Mat(), cv::Point(-1,-1),
                      filter->getParameterValue(0));
            break;

        case CFilter::filterType::Gaussian:
            cv::GaussianBlur(src, dest, cv::Size(filter->getParameterValue(0),
                                                 filter->getParameterValue(0)),
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
    }
    catch(std::exception &e)
    {
        std::cerr << "ImageHandler::useFilter()" << e.what() << std::endl;
        return;
    }
}

void ImageHandler::showMessageBox(QString text, QString title, QMessageBox::Icon icon)
{
    QMessageBox message;
    message.setWindowTitle(title);
    message.setText(text);
    message.setIcon(icon);
    message.exec();
}
