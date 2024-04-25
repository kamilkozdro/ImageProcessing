#ifndef CFILTER_H
#define CFILTER_H

#include <QString>
#include <QMap>
#include <QMessageBox>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"

class CFilter
{
public:

    virtual ~CFilter();

    static CFilter* createFilter(QString filterName);

    virtual void useFilter(cv::Mat& imgSrc, cv::Mat& imgDst) = 0;
    virtual bool checkParameterValid(QString key, float value) = 0;
    static inline QString getFilterName() {return filterName;};
    inline QMap<QString, float> getParameters()
    {
        return parameters;
    }

    void setParameters(QMap<QString, float> newParams);
    void setParameter(QString key, float value);

protected:
    CFilter();

    static QString filterName;
    QMap<QString, float> parameters;

private:
};


class CFilterBlur : public CFilter
{
public:
    CFilterBlur()
    {
        filterName = "Blur";
        parameters["ksize"] = 1;
    };

    inline void useFilter(cv::Mat& imgSrc, cv::Mat& imgDst) override
    {
        cv::blur(imgSrc, imgDst, cv::Size(parameters["ksize"], parameters["ksize"]));
    }

    bool checkParameterValid(QString key, float value) override;

protected:

private:


};

#endif // CFILTER_H
