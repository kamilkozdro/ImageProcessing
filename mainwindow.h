
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

#include "imagehandler.h"
#include "cfilterwidget.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
//#include <QImage>
#include <QPixmap>
#include <QPushButton>
#include <QComboBox>
#include <QStringList>
#include <QLineEdit>
#include <QTimer>
#include <QFileDialog>
#include <QListWidget>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void removeFilter(unsigned int index);

private:

    QImage Mat2QImage(cv::Mat & src);
    void connectSignals();

    ImageHandler imgHandler;
    QTimer *timer;
    //----------*GUI*----------
    QLabel *labelCamWindow1, *labelCamWindow2, *labelCamID, *labelStatus;
    QLabel *labelFilters, *labelUsedFilters;
    QVBoxLayout *mainLayout;
    QHBoxLayout *optionsLayout;
    QGridLayout *camsLayout;
    QGridLayout *firstOptionsLayout;
    QHBoxLayout *secondOptionsLayout;


    QFrame *camsFrame, *firstOptionsFrame, *secondOptionsFrame;
    QPushButton *buttonCam, *buttonAddFilter, *buttonRemoveFilter,
                *buttonLoadImage;
    QComboBox *comboBoxFilters, *comboBoxWindow1, *comboBoxWindow2;
    QListView *listViewUsedFilters;
    QLineEdit *lineEditCamID;
    QListWidget *listWidgetUsedFilters;
    QList<CFilterWidget*> filterWidgetList;
    int lastUsedFilterIndex;

    void selectLastUsedFilterIndex();

private slots:

    void update();
    void onReleased_buttonCam();
    void onReleased_buttonLoadImage();
    void onReleased_buttonAddFilter();
    void onReleased_buttonRemoveFilter();
    void onChanged_comboBoxWindow1(int index);
    void onChanged_comboBoxWindow2(int index);
    void onChanged_usedFilter(int index);
};

#endif // MAINWINDOW_H
