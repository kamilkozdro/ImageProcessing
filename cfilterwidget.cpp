#include "cfilterwidget.h"

CFilterWidget::CFilterWidget(CFilter::filterType filterType, QWidget *parent)
    : QWidget{parent}
{
    try
    {
        switch (filterType)
        {
        case CFilter::filterType::Blur:
            filter = new CFilterBlur();
            break;

        case CFilter::filterType::Sobel:
            filter = new CFilterSobel();
            break;
        case CFilter::filterType::Dilate:
            filter = new CFilterDilate();
            break;
        case CFilter::filterType::Erode:
            filter = new CFilterErode();
            break;
        case CFilter::filterType::Gaussian:
            filter = new CFilterGaussian();
            break;
        case CFilter::filterType::Laplacian:
            filter = new CFilterLaplacian();
            break;
        case CFilter::filterType::Medianblur:
            filter = new CFilterMedianblur();
            break;

        default:
            throw std::invalid_argument("Uknown filterType");
            break;
        }

        initGUI();
    }
    catch(std::exception &e)
    {
        std::cerr << "CFilterWidget::CFilterWidget():" << e.what() << std::endl;
        return;
    }


}

CFilterWidget::~CFilterWidget()
{
    if(filter != nullptr)
    {
        delete filter;
        filter = nullptr;
    }
}

void CFilterWidget::initGUI()
{
    mainLayout = new QVBoxLayout(this);
    formLayout = new QFormLayout();

    dialogButtons = new QDialogButtonBox();
    dialogButtons->addButton("Save", QDialogButtonBox::AcceptRole);

    mainLayout->addWidget(dialogButtons);

    for(int i = 0; i < filter->countParameters(); ++i)
    {
        auto parameterEditLine = new QLineEdit();
        parameterEditLine->setText(QString::number(filter->getParameterValue(i)));
        lineEditList.append(parameterEditLine);
        formLayout->addRow(filter->getParameterName(i), parameterEditLine);
    }
    mainLayout->addLayout(formLayout);

    connect(dialogButtons, SIGNAL(accepted()), this, SLOT(onRelease_buttonOK()));
}

void CFilterWidget::onRelease_buttonOK()
{
    QList<float> newParameterValueList;

    foreach(QLineEdit *lineEdit, lineEditList)
    {
        if(lineEdit->text() == "")
        {
            QMessageBox::information(this, "", "Enter value to parameter edit box");
            return;
        }

        bool ok;
        float newParameterValue = lineEdit->text().toFloat(&ok);
        if(!ok)
        {
            QMessageBox::information(this, "", "Invalid parameter value - not a number");
            return;
        }

        newParameterValueList.append(newParameterValue);
    }

    if(!filter->checkParametersValid(newParameterValueList))
    {
        QMessageBox::information(this, "", "Invalid parameter value");
        return;
    }

    filter->setParametersValues(newParameterValueList);
}
