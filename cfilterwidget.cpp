#include "cfilterwidget.h"

CFilterWidget::CFilterWidget(CFilter* newFilter, QWidget *parent)
    : QWidget{parent}
{
    filter = newFilter;

    initGUI();

}

CFilterWidget::~CFilterWidget()
{
    if (filter != nullptr)
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

    QMap<QString, float> filterParameters = filter->getParameters();
    QMapIterator<QString, float> it(filterParameters);
    while(it.hasNext())
    {
        it.next();
        QLineEdit* parameterEditLine = new QLineEdit();
        parameterEditLine->setText(QString::number(it.value()));
        formLayout->addRow(it.key(), parameterEditLine);
    }

    mainLayout->addLayout(formLayout);

    connect(dialogButtons, SIGNAL(accepted()), this, SLOT(onRelease_buttonOK()));
}

void CFilterWidget::onRelease_buttonOK()
{
    for(int i = 0; i < formLayout->rowCount(); i++)
    {
        bool ok;
        QLayoutItem* labelItem = formLayout->itemAt(i,QFormLayout::LabelRole);
        QString paramName = qobject_cast<QLabel*>(labelItem->widget())->text();

        QLayoutItem* lineEditItem = formLayout->itemAt(i,QFormLayout::FieldRole);
        QString paramValueString = qobject_cast<QLineEdit*>(lineEditItem->widget())->text();
        if (paramValueString == "")
        {
            QMessageBox::information(this, "", "Enter value to parameter edit box");
            return;
        }

        float paramValue = paramValueString.toFloat(&ok);
        if (!ok)
        {
            QMessageBox::information(this, "", "Invalid parameter value - not a number");
            return;
        }

        filter->setParameter(paramName, paramValue);
    }
}
