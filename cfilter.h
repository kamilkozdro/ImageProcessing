#ifndef CFILTER_H
#define CFILTER_H

#include <QMap>
#include <QMessageBox>
#include <QString>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"
#include <vector>

class CFilter
{
public:
    virtual ~CFilter(){};

    static CFilter *createFilter(QString filterName);

    virtual void useFilter(cv::Mat &imgSrc, cv::Mat &imgDst) = 0;
    bool checkParameterValid(QString key, float value);
    virtual QString getFilterName() = 0;
    inline QMap<QString, float> getParameters() { return parameters; }

    void setParameters(QMap<QString, float> newParams);
    void setParameter(QString key, float value);

protected:
    CFilter();

    QMap<QString, float> parameters;

private:
};

class CFilterBlur : public CFilter
{
public:
    CFilterBlur() { parameters["ksize"] = 1; };
    ~CFilterBlur(){};

    inline QString getFilterName() override { return "Blur"; };

    inline void useFilter(cv::Mat &imgSrc, cv::Mat &imgDst) override
    {
        cv::blur(imgSrc, imgDst, cv::Size(parameters["ksize"], parameters["ksize"]));
    }

protected:
private:
};

class CFilterErode : public CFilter
{
public:
    CFilterErode() { parameters["iterations"] = 1; };
    ~CFilterErode(){};

    inline QString getFilterName() override { return "Erode"; };

    inline void useFilter(cv::Mat &imgSrc, cv::Mat &imgDst) override
    {
        cv::erode(imgSrc, imgDst, cv::Mat(), cv::Point(-1, -1), parameters["iterations"]);
    }

protected:
private:
};

class CFilterDilate : public CFilter
{
public:
    CFilterDilate() { parameters["iterations"] = 1; };
    ~CFilterDilate(){};

    inline QString getFilterName() override { return "Dilate"; };

    inline void useFilter(cv::Mat &imgSrc, cv::Mat &imgDst) override
    {
        cv::dilate(imgSrc, imgDst, cv::Mat(), cv::Point(-1, -1), parameters["iterations"]);
    }

protected:
private:
};

class CFilterGaussianBlur : public CFilter
{
public:
    CFilterGaussianBlur()
    {
        parameters["ksize"] = 1;
        parameters["sigmaX"] = 0;
        parameters["sigmaY"] = 0;
    };
    ~CFilterGaussianBlur(){};

    inline QString getFilterName() override { return "GaussianBlur"; };

    inline void useFilter(cv::Mat &imgSrc, cv::Mat &imgDst) override
    {
        cv::GaussianBlur(imgSrc, imgDst, cv::Size(parameters["ksize"], parameters["ksize"])
                         ,parameters["sigmaX"], parameters["sigmaY"]);
    }

protected:
private:
};

class CFilterLaplacian : public CFilter
{
public:
    CFilterLaplacian()
    {
        parameters["ksize"] = 1;
    };
    ~CFilterLaplacian(){};

    inline QString getFilterName() override { return "Laplacian"; };

    inline void useFilter(cv::Mat &imgSrc, cv::Mat &imgDst) override
    {
        // ddepth=-1, the output image will have the same depth as the source
        cv::Laplacian(imgSrc, imgDst, CV_8U, parameters["ksize"]);
    }

protected:
private:
};

class CFilterSobel : public CFilter
{
public:
    CFilterSobel()
    {
        parameters["dx"] = 1;
        parameters["dy"] = 1;
        parameters["ksize"] = 1;
    };
    ~CFilterSobel(){};

    inline QString getFilterName() override { return "Sobel"; };

    inline void useFilter(cv::Mat &imgSrc, cv::Mat &imgDst) override
    {
        // ddepth=-1, the output image will have the same depth as the source
        cv::Sobel(imgSrc, imgDst, -1, parameters["dx"], parameters["dy"],
                  parameters["ksize"]);
    }

protected:
private:
};


#endif // CFILTER_H
