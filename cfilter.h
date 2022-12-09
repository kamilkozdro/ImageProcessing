#ifndef CFILTER_H
#define CFILTER_H

#include <QString>
#include <QList>

#include <iostream>

class CFilter
{   
protected:
    CFilter();

public:

    enum class filterType{ None, Blur, Sobel, Dilate, Erode,
                           Gaussian, Laplacian, Medianblur};

    virtual ~CFilter();

    void setType(filterType newFilterType) {type = newFilterType;};
    filterType getType() {return type;};
    void addParameter(QString paramaterName, float parameterValue);
    void setParameter(QString paramaterName, float newParameterValue);
    void setParameterValue(unsigned int  index, float newParameterValue);
    void setParametersValues(QList<float> newParameterValueList);
    float getParameterValue(QString paramaterName);
    float getParameterValue(unsigned int  index);
    QList<float> getParameterValues() {return parameterValueList;};
    QString getParameterName(unsigned int index);
    qsizetype countParameters() {return parameterNameList.count();};
    virtual bool checkParametersValid(QList<float> newParameterList) = 0;
    static filterType stringToType(QString stringType);
    static QString typeToString(filterType type);

private:
    QList<QString> parameterNameList;
    QList<float> parameterValueList;
    filterType type;

protected:
    void throwInvalidParameterListSize(QList<float> &list, int size);

};


class CFilterSobel : public CFilter
{
public:
    CFilterSobel();
    virtual ~CFilterSobel(){};

    bool checkParametersValid(QList<float> newParameterList);
};

class CFilterBlur : public CFilter
{
public:
    CFilterBlur();
    virtual ~CFilterBlur(){};

    bool checkParametersValid(QList<float> newParameterList);
};

class CFilterDilate : public CFilter
{
public:
    CFilterDilate();
    virtual ~CFilterDilate(){};

    bool checkParametersValid(QList<float> newParameterList);
};

class CFilterErode : public CFilter
{
public:
    CFilterErode();
    virtual ~CFilterErode(){};

    bool checkParametersValid(QList<float> newParameterList);
};

class CFilterGaussian : public CFilter
{
public:
    CFilterGaussian();
    virtual ~CFilterGaussian(){};

    bool checkParametersValid(QList<float> newParameterList);
};

class CFilterLaplacian : public CFilter
{
public:
    CFilterLaplacian();
    virtual ~CFilterLaplacian(){};

    bool checkParametersValid(QList<float> newParameterList);
};

class CFilterMedianblur : public CFilter
{
public:
    CFilterMedianblur();
    virtual ~CFilterMedianblur(){};

    bool checkParametersValid(QList<float> newParameterList);
};

#endif // CFILTER_H
