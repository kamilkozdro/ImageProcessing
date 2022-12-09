#include "cfilter.h"

CFilter::CFilter()
{

}

CFilter::~CFilter()
{

}

void CFilter::addParameter(QString paramaterName, float parameterValue)
{
    try
    {

    }
    catch(std::exception &e)
    {
        std::cerr << "" << e.what() << std::endl;
    }

    if(!parameterNameList.contains(paramaterName))
    {
        parameterNameList.append(paramaterName);
        parameterValueList.append(parameterValue);
    }
    else
    {
         //THROW ERROR
    }
}

void CFilter::setParameter(QString paramaterName, float newParameterValue)
{
    try
    {

    }
    catch(std::exception &e)
    {
        std::cerr << "" << e.what() << std::endl;
    }

    if(parameterNameList.contains(paramaterName))
    {
        qsizetype index = parameterNameList.indexOf(paramaterName);
        parameterValueList.replace(index, newParameterValue);
    }
    else
    {
        //THROW ERROR
    }
}

void CFilter::setParameterValue(unsigned int index, float newParameterValue)
{
    try
    {

    }
    catch(std::exception &e)
    {
        std::cerr << "" << e.what() << std::endl;
    }

    if(index < countParameters())
    {
        parameterValueList.replace(index, newParameterValue);
    }
    else
    {
         //THROW ERROR
    }
}

void CFilter::setParametersValues(QList<float> newParameterValueList)
{
    try
    {

    }
    catch(std::exception &e)
    {
        std::cerr << "" << e.what() << std::endl;
    }

    if(parameterValueList.count() != newParameterValueList.count())
    {
        // THROW ERROR - INVALID NUMBER OF VALUES
        return;
    }

    for(int i = 0; i < parameterValueList.count(); ++i)
    {
        parameterValueList.replace(i, newParameterValueList.value(i));
    }
}

float CFilter::getParameterValue(QString paramaterName)
{

    try
    {

    }
    catch(std::exception &e)
    {
        std::cerr << "" << e.what() << std::endl;
    }

    qsizetype index = parameterNameList.indexOf(paramaterName);
    if(index != -1)
    {
        return parameterValueList.value(index);
    }
    else
    {
        //THROW ERROR
        return -1;
    }
}

float CFilter::getParameterValue(unsigned int  index)
{
    try
    {

    }
    catch(std::exception &e)
    {
        std::cerr << "" << e.what() << std::endl;
    }

    if(index < countParameters())
    {
        return parameterValueList.value(index);
    }
    else
    {
        //THROW ERROR
        return -1;
    }
}

QString CFilter::getParameterName(unsigned int index)
{
    try
    {
        if(index < countParameters())
        {
            return parameterNameList.value(index);
        }
        else
        {
            throw std::out_of_range("Index bigger than parameterNameList size");
        }
    }
    catch(std::exception &e)
    {
        std::cerr << "CFilter::getParameterName():" << e.what() << std::endl;
        return "";
    }


}

CFilter::filterType CFilter::stringToType(QString stringType)
{
    if(stringType == "Blur")
        return filterType::Blur;
    else if(stringType == "Sobel")
        return filterType::Sobel;
    else if(stringType == "Dilate")
        return filterType::Dilate;
    else if(stringType == "Erode")
        return filterType::Erode;
    else if(stringType == "Gaussian")
        return filterType::Gaussian;
    else if(stringType == "Laplacian")
        return filterType::Laplacian;
    else if(stringType == "Medianblur")
        return filterType::Medianblur;
    else
        return filterType::None;
}

QString CFilter::typeToString(filterType type)
{
    if(type == filterType::Blur)
        return "Blur";
    else if(type == filterType::Sobel)
        return "Sobel";
    else if(type == filterType::Dilate)
        return "Dilate";
    else if(type == filterType::Erode)
        return "Erode";
    else if(type == filterType::Gaussian)
        return "Gaussian";
    else if(type == filterType::Laplacian)
        return "Laplacian";
    else if(type == filterType::Medianblur)
        return "Medianblur";
    else
        return "";
}

void CFilter::throwInvalidParameterListSize(QList<float> &list, int size)
{
    if(list.count() != size)
    {
        throw std::invalid_argument("Invalid ParameterList size");
    };

}



// *************************** CFilterSobel *******************************

CFilterSobel::CFilterSobel()
{
    addParameter("dx", 1);
    addParameter("dy", 0);
    addParameter("ksize", 1);
    setType(filterType::Sobel);
}

bool CFilterSobel::checkParametersValid(QList<float> newParameterList)
{

    try
    {
        throwInvalidParameterListSize(newParameterList, 3);

        int dx = static_cast<int> (newParameterList.value(0));
        int dy = static_cast<int> (newParameterList.value(1));
        int ksize = static_cast<int>(newParameterList.value(2));

        // dx/dy must be 0 or 1
        if ((dx != 0 && dx != 1) && (dy != 0 && dy != 1))
        {
            return false;
        }

        // ksize must be 1,3,5 or 7
        if((ksize != 1) && (ksize != 3) && (ksize != 5) && (ksize != 7))
        {
            return false;
        }

        return true;
    }
    catch(std::exception &e)
    {
        std::cerr << "CFilterSobel::checkParametersValid():" << e.what() << std::endl;
        return false;
    }
}

// *************************** CFilterBlur *******************************

CFilterBlur::CFilterBlur()
{
    addParameter("ksize", 1);
    setType(filterType::Blur);
}

bool CFilterBlur::checkParametersValid(QList<float> newParameterList)
{

    try
    {
        throwInvalidParameterListSize(newParameterList, 1);

        int ksize = static_cast<int>(newParameterList.value(0));

        // 31 - max ksize
        if( (ksize < 1) || (ksize > 31) || (ksize%2 != 1))
        {
            return false;
        }

        return true;
    }
    catch(std::exception &e)
    {
        std::cerr << "CFilterBlur::checkParametersValid():" << e.what() << std::endl;
        return false;
    }
}

// *************************** CFilterDilate *******************************

CFilterDilate::CFilterDilate()
{
    addParameter("iterations", 1);
    setType(filterType::Dilate);
}

bool CFilterDilate::checkParametersValid(QList<float> newParameterList)
{
    try
    {
        throwInvalidParameterListSize(newParameterList, 1);

        int iterations = static_cast<int>(newParameterList.value(0));
        if(iterations < 1 || iterations > 30)
        {
            return false;
        }

        return true;
    }
    catch(std::exception &e)
    {
        std::cerr << "CFilterDilate::checkParametersValid():" << e.what() << std::endl;
        return false;
    }


}

// *************************** CFilterErode *******************************

CFilterErode::CFilterErode()
{
    addParameter("iterations", 1);
    setType(filterType::Erode);
}

bool CFilterErode::checkParametersValid(QList<float> newParameterList)
{
    try
    {
        throwInvalidParameterListSize(newParameterList, 1);

        int iterations = static_cast<int>(newParameterList.value(0));
        if(iterations < 1 || iterations > 30)
        {
            return false;
        }

        return true;
    }
    catch(std::exception &e)
    {
        std::cerr << "CFilterErode::checkParametersValid():" << e.what() << std::endl;
        return false;
    }
}

// *************************** CFilterGaussian *******************************

CFilterGaussian::CFilterGaussian()
{
    addParameter("ksize", 1);
    addParameter("sigmaX", 1);
    addParameter("sigmaY", 0);
    setType(filterType::Gaussian);
}

bool CFilterGaussian::checkParametersValid(QList<float> newParameterList)
{

    try
    {
        throwInvalidParameterListSize(newParameterList, 3);

        int ksize = static_cast<int>(newParameterList.value(0));
        // 31 - max ksize
        if( (ksize < 1) || (ksize > 31) || (ksize%2 != 1))
        {
            return false;
        }

        float sigmaX = newParameterList.value(1);
        if(sigmaX < 0 || sigmaX > 5)
        {
            return false;
        }

        float sigmaY = newParameterList.value(2);
        if(sigmaY < 0 || sigmaY > 5)
        {
            return false;
        }

        return true;
    }
    catch(std::exception &e)
    {
        std::cerr << "CFilterGaussian::checkParametersValid():" << e.what() << std::endl;
        return false;
    }
}

// *************************** CFilterLaplacian *******************************

CFilterLaplacian::CFilterLaplacian()
{
    addParameter("ksize", 1);
    setType(filterType::Laplacian);
}

bool CFilterLaplacian::checkParametersValid(QList<float> newParameterList)
{

    try
    {
        throwInvalidParameterListSize(newParameterList, 1);

        int ksize = static_cast<int>(newParameterList.value(0));
        // 31 - max ksize
        if( (ksize < 1) || (ksize > 31) || (ksize%2 != 1))
        {
            return false;
        }

        return true;
    }
    catch(std::exception &e)
    {
        std::cerr << "CFilterLaplacian::checkParametersValid():" << e.what() << std::endl;
        return false;
    }
}

// *************************** CFilterMedianblur *******************************

CFilterMedianblur::CFilterMedianblur()
{
    addParameter("ksize", 1);
    setType(filterType::Medianblur);
}

bool CFilterMedianblur::checkParametersValid(QList<float> newParameterList)
{

    try
    {
        throwInvalidParameterListSize(newParameterList, 1);

        int ksize = static_cast<int>(newParameterList.value(0));
        // 31 - max ksize
        if( (ksize < 1) || (ksize > 31) || (ksize%2 != 1))
        {
            return false;
        }

        return true;
    }
    catch(std::exception &e)
    {
        std::cerr << "CFilterMedianblur::checkParametersValid():" << e.what() << std::endl;
        return false;
    }
}
