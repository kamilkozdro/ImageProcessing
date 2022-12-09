#ifndef CFILTERWIDGET_H
#define CFILTERWIDGET_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QMessageBox>
#include "cfilter.h"

#include <iostream>
#include <stdexcept>

class CFilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CFilterWidget(CFilter::filterType filterType, QWidget *parent = nullptr);
    ~CFilterWidget();


    void initGUI();
    QList<float> getFilterValues() {return filter->getParameterValues();};
    CFilter::filterType getFilterType() {return filter->getType();};
    CFilter* getFilterPtr() {return filter;};

private:

    //----------*GUI*----------
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QList<QLineEdit*> lineEditList;
    QList<QString> labelsNames;
    QDialogButtonBox *dialogButtons;
    //-------------------------
    CFilter *filter;

private slots:
    void onRelease_buttonOK();

signals:

};

#endif // CFILTERWIDGET_H
