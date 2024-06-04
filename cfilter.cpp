#include "cfilter.h"

CFilter::CFilter() {}

CFilter *CFilter::createFilter(QString filterName)
{
    if (filterName == CFilterBlur().getFilterName())
        return new CFilterBlur();
    else if (filterName == CFilterErode().getFilterName())
        return new CFilterErode();
    else if (filterName == CFilterDilate().getFilterName())
        return new CFilterDilate();
    else if (filterName == CFilterGaussianBlur().getFilterName())
        return new CFilterGaussianBlur();
    else if (filterName == CFilterLaplacian().getFilterName())
        return new CFilterLaplacian();
    else if (filterName == CFilterSobel().getFilterName())
        return new CFilterSobel();

    else
        return nullptr;
}

void CFilter::setParameters(QMap<QString, float> newParams)
{
    // Iterate through newParams and set value of parameters if keys match
    QMapIterator<QString, float> it(newParams);
    while (it.hasNext()) {
        it.next();
        if (checkParameterValid(it.key(), it.value()))
            parameters[it.key()] = it.value();
    }
}

void CFilter::setParameter(QString key, float value)
{
    if (checkParameterValid(key, value))
        parameters[key] = value;
}

bool CFilter::checkParameterValid(QString key, float value)
{
    if (!parameters.contains(key))
    {
        QMessageBox::warning(nullptr, "", "Invalid parameter name");
        return false;
    }

    if (key == "iterations")
    {
        int intValue = (int) value;
        if (intValue <= 0)
        {
            QMessageBox::warning(nullptr, "", "iterations must be integer positive");
            return false;
        }
    }
    else if (key == "ksize")
    {
        int intValue = (int) value;
        if (intValue % 2 != 1 || value <= 0)
        {
            QMessageBox::warning(nullptr, "", "ksize must be integer positive odd number");
            return false;
        }
    }
    else if (key == "sigmaX" || key == "sigmaY")
    {
        if (value < 0 || value > 100)
        {
            QMessageBox::warning(nullptr, "", "sigma must be float between 0 - 100");
            return false;
        }
    }
    else if (key == "dx" || key == "dx")
    {
        int intValue = (int) value;
        if (intValue != 0 && intValue != 1)
        {
            QMessageBox::warning(nullptr, "", "derivative must be 0 or 1");
            return false;
        }
    }

    else
        return false;

    return true;
}
