#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Image Processing");

    ui->filtersComboBox->addItem(CFilterBlur().getFilterName());
    ui->filtersComboBox->addItem(CFilterGaussianBlur().getFilterName());
    ui->filtersComboBox->addItem(CFilterErode().getFilterName());
    ui->filtersComboBox->addItem(CFilterDilate().getFilterName());
    ui->filtersComboBox->addItem(CFilterLaplacian().getFilterName());
    ui->filtersComboBox->addItem(CFilterSobel().getFilterName());

    ui->selectedFrameComboBoxLeft->addItem("Origin frame");
    ui->selectedFrameComboBoxRight->addItem("Origin frame");

    lastUsedFilterIndex = -1;

    imgSource = nullptr;

    imageCameraSourceTimer = new QTimer(this);
    imageCameraSourceTimer->setInterval(100);
    connectSignals();
}

MainWindow::~MainWindow()
{
    if (imgSource != nullptr) {
        if (imgSource->isOpen())
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
    connect(imageCameraSourceTimer, &QTimer::timeout,
            this, &MainWindow::update);
    connect(ui->camButton, &QPushButton::released,
            this, &MainWindow::onReleased_buttonCam);
    connect(ui->loadImageButton, &QPushButton::released,
            this, &MainWindow::onReleased_buttonLoadImage);
    connect(ui->addFilterButton, &QPushButton::released,
            this, &MainWindow::onReleased_buttonAddFilter);
    connect(ui->removeFilterButton, &QPushButton::released,
            this, &MainWindow::onReleased_buttonRemoveFilter);
    connect(ui->selectedFrameComboBoxLeft, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onChanged_comboBoxWindowLeft(int)));
    connect(ui->selectedFrameComboBoxRight, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onChanged_comboBoxWindowRight(int)));
    connect(ui->usedFiltersList, SIGNAL(currentRowChanged(int)),
            this, SLOT(onChanged_usedFilter(int)));
}

void MainWindow::update()
{
    QImage rightFrame, leftFrame;
    int rightWindowSelectedFilterIndex, leftWindowSelectedFilterIndex;
    cv::Mat srcImg;

    if (imgSource == nullptr)
        return;

    if (!imgSource->isOpen())
        return;

    srcImg = imgSource->getImage();

    // Update right window
    rightWindowSelectedFilterIndex = ui->selectedFrameComboBoxRight->currentIndex();
    processImage(srcImg, rightWindowImg, rightWindowSelectedFilterIndex);
    rightFrame = Mat2QImage(rightWindowImg);
    ui->camWindowRight->setPixmap(QPixmap::fromImage(rightFrame));

    // Update left window
    leftWindowSelectedFilterIndex = ui->selectedFrameComboBoxLeft->currentIndex();
    processImage(srcImg, leftWindowImg, leftWindowSelectedFilterIndex);
    leftFrame = Mat2QImage(leftWindowImg);
    ui->camWindowLeft->setPixmap(QPixmap::fromImage(leftFrame));

}

void MainWindow::removeFilter(unsigned int index)
{
    ui->selectedFrameComboBoxLeft->removeItem(index + 1); // +1 because Origin Fram is at index 0
    ui->selectedFrameComboBoxRight->removeItem(index + 1);

    QListWidgetItem *indexToRemove = ui->usedFiltersList->takeItem(index);
    delete indexToRemove;
    QWidget *widgetToDelete = filterWidgetList.takeAt(index);
    delete widgetToDelete;
}

bool MainWindow::openNewImageSource(CImageSource *newImgSource, QString args)
{
    imageCameraSourceTimer->stop();
    if (imgSource != nullptr) {
        imgSource->close();
        delete imgSource;
        imgSource = nullptr;
    }

    newImgSource->open(args);

    if (!newImgSource->isOpen()) {
        return false;
    }

    imgSource = newImgSource;
    return true;
}

void MainWindow::onReleased_buttonLoadImage()
{
    CImageFileSource *newImgSource = new CImageFileSource();
    if (!openNewImageSource(newImgSource)) {
        delete newImgSource;
        newImgSource = nullptr;
        return;
    }

    update();
}

void MainWindow::onReleased_buttonCam()
{
    CImageCameraSource *newImgSource = new CImageCameraSource();
    QString camID = ui->camIDSpinBox->text();

    if (!openNewImageSource(newImgSource, camID)) {
        delete newImgSource;
        newImgSource = nullptr;
        ui->camButton->setText("Open Cam");
        return;
    }

    imageCameraSourceTimer->start();
    //ui->camButton->setText("Close Cam");
}

void MainWindow::onReleased_buttonAddFilter()
{
    QString chosenFilterName = ui->filtersComboBox->currentText();
    CFilter *newFilter = CFilter::createFilter(chosenFilterName);
    if (newFilter == nullptr) {
        qDebug() << "MainWindow::onReleased_buttonAddFilter() - newFilter is nullptr";
        return;
    }
    CFilterWidget *filterWidget = new CFilterWidget(newFilter);

    connect(filterWidget, &CFilterWidget::buttonSavedClicked,
            this, &MainWindow::update);

    ui->usedFiltersList->addItem(chosenFilterName);

    ui->selectedFrameComboBoxLeft->addItem(chosenFilterName);
    ui->selectedFrameComboBoxRight->addItem(chosenFilterName);

    filterWidgetList.append(filterWidget);
    filterWidget->hide();

    ui->filterParamsBox->layout()->addWidget(filterWidget);

    selectLastUsedFilterIndex();
}

void MainWindow::onReleased_buttonRemoveFilter()
{
    if (ui->usedFiltersList->count() > 0) {
        removeFilter(ui->usedFiltersList->currentRow());
        selectLastUsedFilterIndex();
    }
}

void MainWindow::onChanged_comboBoxWindowLeft(int index)
{
    update();
}

void MainWindow::onChanged_comboBoxWindowRight(int index)
{
    update();
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
    if (indexCount >= 0) {
        ui->usedFiltersList->setCurrentRow(indexCount - 1);
        lastUsedFilterIndex = indexCount - 1;
    } else
        lastUsedFilterIndex = -1;
}

void MainWindow::processImage(cv::Mat &src, cv::Mat &dst, int lastFilterIndex)
{
    if (lastFilterIndex < 0 || lastFilterIndex > filterWidgetList.count())
        lastFilterIndex = filterWidgetList.count();

    src.copyTo(dst);

    for (int i = 0; i < lastFilterIndex; ++i) {
        filterWidgetList.at(i)->getFilterPtr()->useFilter(dst, dst);
    }
}
