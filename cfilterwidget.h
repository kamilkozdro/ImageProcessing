#ifndef CFILTERWIDGET_H
#define CFILTERWIDGET_H

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include <QMessageBox>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include "cfilter.h"

#include <QDebug>

#include <iostream>
#include <stdexcept>

class CFilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CFilterWidget(CFilter *newFilter, QWidget *parent = nullptr);
    ~CFilterWidget();

    void initGUI();
    CFilter *getFilterPtr() { return filter; };

private:
    //----------*GUI*----------
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QDialogButtonBox *dialogButtons;
    //-------------------------
    CFilter *filter;

private slots:
    void onRelease_buttonSave();

signals:
    void buttonSavedClicked();
};

#endif // CFILTERWIDGET_H
