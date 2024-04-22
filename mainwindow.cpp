/*
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Image Processing");

    ui->filtersComboBox->addItem(CFilter::typeToString(CFilter::filterType::Blur));
    ui->filtersComboBox->addItem(CFilter::typeToString(CFilter::filterType::Medianblur));
    ui->filtersComboBox->addItem(CFilter::typeToString(CFilter::filterType::Dilate));
    ui->filtersComboBox->addItem(CFilter::typeToString(CFilter::filterType::Erode));
    ui->filtersComboBox->addItem(CFilter::typeToString(CFilter::filterType::Sobel));
    ui->filtersComboBox->addItem(CFilter::typeToString(CFilter::filterType::Gaussian));
    ui->filtersComboBox->addItem(CFilter::typeToString(CFilter::filterType::Laplacian));

    ui->selectedFrameComboBoxLeft->addItem("Unchanged frame");
    ui->selectedFrameComboBoxRight->addItem("Unchanged frame");

    lastUsedFilterIndex = -1;

    imgSource = nullptr;

    imageCameraSourceTimer = new QTimer(this);
    imageCameraSourceTimer->setInterval(500);
    connectSignals();
}

MainWindow::~MainWindow()
{
    if(imgSource != nullptr)
    {
        if(imgSource->isOpen())
            imgSource->close();
        delete imgSource;
        imgSource = nullptr;
    }

    delete ui;
}

QImage MainWindow::Mat2QImage(cv::Mat &src)
{
    cv::Mat temp;
    cvtColor(src, temp, cv::COLOR_BGR2RGB);
    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits(); // enforce deep copy, see documentation
                // of QImage::QImage ( const uchar * data, int width, int height, Format format )
    return dest;
}

void MainWindow::connectSignals()
{
    connect(imageCameraSourceTimer, &QTimer::timeout, this, &MainWindow::update);
    connect(ui->camButton, &QPushButton::released, this, &MainWindow::onReleased_buttonCam);
    connect(ui->loadImageButton, &QPushButton::released, this, &MainWindow::onReleased_buttonLoadImage);
    connect(ui->addFilterButton, &QPushButton::released, this, &MainWindow::onReleased_buttonAddFilter);
    connect(ui->removeFilterButton, &QPushButton::released, this, &MainWindow::onReleased_buttonRemoveFilter);
    connect(ui->selectedFrameComboBoxLeft, SIGNAL(currentIndexChanged(int)), this, SLOT(onChanged_comboBoxWindowLeft(int)));
    connect(ui->selectedFrameComboBoxRight, SIGNAL(currentIndexChanged(int)), this, SLOT(onChanged_comboBoxWindowRight(int)));
    connect(ui->usedFiltersList, SIGNAL(currentRowChanged(int)), this, SLOT(onChanged_usedFilter(int)));
}

void MainWindow::update()
{
    // ODSWIEZAC TYLKO PRZY DODANIU FILTRU LUB ZMIANIE PARAMETROW

    if(imgSource == nullptr)
        return;

    if(!imgSource->isOpen())
        return;


    QImage frame1, frame2;
    cv::Mat cvFrame;
    //imgHandler.updateObject();
    //imgHandler.getFrame1().copyTo(cvFrame); //kopiowanie obrazu - SLABOOOOO

    frame1 = Mat2QImage(imgSource->getImage());
    //imgHandler.getFrame2().copyTo(cvFrame); //kopiowanie obrazu - SLABOOOOO
    frame2 = Mat2QImage(imgSource->getImage());
    ui->camWindowLeft->setPixmap(QPixmap::fromImage(frame1));
    ui->camWindowRight->setPixmap(QPixmap::fromImage(frame2));

}

void MainWindow::removeFilter(unsigned int index)
{
    imgHandler.removeFilter(index);

    ui->selectedFrameComboBoxLeft->removeItem(index + 1); // +1, bo zawsze jest Unchanged Frame na index = 0
    ui->selectedFrameComboBoxRight->removeItem(index + 1);

    QListWidgetItem *indexToRemove = ui->usedFiltersList->takeItem(index);
    delete indexToRemove;
    QWidget *widgetToDelete = filterWidgetList.takeAt(index);
    delete widgetToDelete;
}

bool MainWindow::openNewImageSource(CImageSource* newImgSource, QString args)
{
    imageCameraSourceTimer->stop();
    if(imgSource != nullptr)
    {
        imgSource->close();
        delete imgSource;
        imgSource = nullptr;
    }

    newImgSource->open(args);

    if(!newImgSource->isOpen())
    {
        return false;
    }

    imgSource = newImgSource;
    return true;
}

void MainWindow::onReleased_buttonLoadImage()
{

    CImageFileSource* newImgSource = new CImageFileSource();
    if(!openNewImageSource(newImgSource))
    {
        delete newImgSource;
        newImgSource = nullptr;
        return;
    }

    imgHandler.setFrame(imgSource->getImage());
    update();
}

void MainWindow::onReleased_buttonCam()
{

    CImageCameraSource* newImgSource = new CImageCameraSource();
    QString camID = ui->camIDSpinBox->text();

    if(!openNewImageSource(newImgSource, camID))
    {
        delete newImgSource;
        newImgSource = nullptr;
        ui->camButton->setText("Open Cam");
        return;
    }

    imageCameraSourceTimer->start();
    imgHandler.setFrame(imgSource->getImage());
    ui->camButton->setText("Close Cam");

}

void MainWindow::onReleased_buttonAddFilter()
{
    QString chosenFilterName = ui->filtersComboBox->currentText();
    CFilter::filterType chosenFilterType = CFilter::stringToType(chosenFilterName);
    CFilterWidget *filterWidget = new CFilterWidget(chosenFilterType);

    imgHandler.addFilter(filterWidget->getFilterPtr());

    ui->usedFiltersList->addItem(chosenFilterName);

    ui->selectedFrameComboBoxLeft->addItem(chosenFilterName);
    ui->selectedFrameComboBoxRight->addItem(chosenFilterName);

    filterWidgetList.append(filterWidget);
    filterWidget->hide();

    ui->filterOptionsLayout->addWidget(filterWidget);

    selectLastUsedFilterIndex();
}

void MainWindow::onReleased_buttonRemoveFilter()
{
    if (ui->usedFiltersList->count() > 0)
    {
        removeFilter(ui->usedFiltersList->currentRow());
        selectLastUsedFilterIndex();
    }
}

void MainWindow::onChanged_comboBoxWindowLeft(int index)
{
    imgHandler.setKeptFrame1(index);
}

void MainWindow::onChanged_comboBoxWindowRight(int index)
{
    imgHandler.setKeptFrame2(index);
}

void MainWindow::onChanged_usedFilter(int index)
{
    if (index < 0)
        return;

    if (lastUsedFilterIndex >= 0)
        filterWidgetList.at(lastUsedFilterIndex)->hide();

    lastUsedFilterIndex = index;
    filterWidgetList.at(lastUsedFilterIndex)->show();
}

void MainWindow::selectLastUsedFilterIndex()
{
    int indexCount = ui->usedFiltersList->count();
    if (indexCount >= 0)
    {
        ui->usedFiltersList->setCurrentRow(indexCount - 1);
        lastUsedFilterIndex = indexCount - 1;
    } else
        lastUsedFilterIndex = -1;
}
