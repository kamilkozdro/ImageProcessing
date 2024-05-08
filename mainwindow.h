#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CImageSource.h"
#include "cfilterwidget.h"
#include "cimagehandler.h"
#include "cimagecamerasource.h"
#include "cimagefilesource.h"

#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QMainWindow>
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
    CImageSource* imgSource;
    cv::Mat srcImg;
    cv::Mat leftWindowImg;
    cv::Mat rightWindowImg;
    CImageHandler LeftImgHandler;
    CImageHandler RightImgHandler;
    QTimer *imageCameraSourceTimer;
    QList<CFilterWidget*> filterWidgetList;
    int lastUsedFilterIndex;

    QImage Mat2QImage(cv::Mat &src);
    void connectSignals();
    bool openNewImageSource(CImageSource* newImgSource, QString args = "");
    void selectLastUsedFilterIndex();
    void processImage(cv::Mat& src, cv::Mat& dst, int lastFilterIndex = -1);
    void getNewSrcImg();
    void updateLeftWindow();
    void updateRightWindow();

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
