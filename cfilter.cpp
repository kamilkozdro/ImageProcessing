#include "cfilter.h"

CFilter::CFilter() {}

CFilter* CFilter::createFilter(QString filterName)
{
    if(filterName == CFilterBlur().getFilterName())
        return new CFilterBlur();
    else if(filterName == CFilterErode().getFilterName())
        return new CFilterErode();
    else
        return nullptr;
}

void CFilter::setParameters(QMap<QString, float> newParams)
{
    // Iterate through newParams and set value of parameters if keys match
    QMapIterator<QString, float> it(newParams);
    while (it.hasNext())
    {
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

bool CFilterBlur::checkParameterValid(QString key, float value)
{
    if(!parameters.contains(key))
    {
        QMessageBox::warning(nullptr, "", "Invalid parameter name");
        return false;
    }

    int intValue = (int)value;

    if(key == "ksize")
    {
        if(intValue%2 != 1 || value <= 0)
        {
            QMessageBox::warning(nullptr, "", "ksize must be positive odd number");
            return false;
        }
    }

    return true;
}

bool CFilterErode::checkParameterValid(QString key, float value)
{
    if(!parameters.contains(key))
    {
        QMessageBox::warning(nullptr, "", "Invalid parameter name");
        return false;
    }

    int intValue = (int)value;

    if(key == "iterations")
    {
        if(intValue <= 0)
        {
            QMessageBox::warning(nullptr, "", "iterations must be positive");
            return false;
        }
    }

    return true;
}
