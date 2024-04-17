
/*
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cfilterwidget.h"
#include "cimagehandler.h"

#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QMainWindow>
//#include <QImage>
#include <QComboBox>
#include <QFileDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QPixmap>
#include <QPushButton>
#include <QStringList>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void removeFilter(unsigned int index);

private:
    Ui::MainWindow *ui;

    QImage Mat2QImage(cv::Mat &src);
    void connectSignals();

    CImageHandler imgHandler;
    QTimer *timer;

    QList<CFilterWidget *> filterWidgetList;
    int lastUsedFilterIndex;

    void selectLastUsedFilterIndex();

private slots:

    void update();
    void onReleased_buttonCam();
    void onReleased_buttonLoadImage();
    void onReleased_buttonAddFilter();
    void onReleased_buttonRemoveFilter();
    void onChanged_comboBoxWindowLeft(int index);
    void onChanged_comboBoxWindowRight(int index);
    void onChanged_usedFilter(int index);
};

#endif // MAINWINDOW_H
