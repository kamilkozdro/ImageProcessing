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

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle("Image Processing");

    mainLayout = new QVBoxLayout(this);
    camsFrame = new QFrame();
    camsLayout = new QGridLayout(camsFrame);
    optionsLayout = new QHBoxLayout();
    firstOptionsFrame = new QFrame();
    firstOptionsLayout = new QGridLayout(firstOptionsFrame);
    secondOptionsFrame = new QFrame();
    secondOptionsLayout = new QHBoxLayout(secondOptionsFrame);

    camsFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

    optionsLayout->setSpacing(10);

    firstOptionsFrame->setMaximumWidth(350);
    firstOptionsFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

    secondOptionsFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

    labelCamWindow1 = new QLabel();
    labelCamWindow2 = new QLabel();
    labelCamID = new QLabel("Cam ID");
    labelStatus = new QLabel("Status");
    labelFilters = new QLabel("Filters:");
    labelUsedFilters = new QLabel("Used Filters:");

    QList<QLabel*> labels;
    labels << labelCamID << labelStatus << labelFilters << labelUsedFilters;

    foreach(QLabel *label,labels)
    {
        label->setAlignment(Qt::AlignCenter);
        label->setMaximumHeight(30);
        label->setMaximumWidth(100);
    }

    buttonCam = new QPushButton("Open Cam");
    buttonLoadImage = new QPushButton("Load Image");
    buttonAddFilter = new QPushButton("Add");
    buttonRemoveFilter = new QPushButton("Remove");

    QList<QPushButton*> buttons;
    buttons << buttonCam << buttonLoadImage << buttonAddFilter << buttonRemoveFilter;

    foreach(QPushButton *button, buttons)
    {
        button->setFixedSize(100,30);
    }

    lineEditCamID = new QLineEdit("0");
    lineEditCamID->setMaximumWidth(20);

    comboBoxFilters = new QComboBox;
    comboBoxWindow1 = new QComboBox;
    comboBoxWindow2 = new QComboBox;

    QList<QComboBox*> comboBoxes;
    comboBoxes << comboBoxFilters << comboBoxWindow1 << comboBoxWindow2;
    foreach(QComboBox *comboBox,comboBoxes)
    {
        comboBox->setMaximumWidth(150);
    }

    comboBoxFilters->addItem(CFilter::typeToString(CFilter::filterType::Blur));
    comboBoxFilters->addItem(CFilter::typeToString(CFilter::filterType::Medianblur));
    comboBoxFilters->addItem(CFilter::typeToString(CFilter::filterType::Dilate));
    comboBoxFilters->addItem(CFilter::typeToString(CFilter::filterType::Erode));
    comboBoxFilters->addItem(CFilter::typeToString(CFilter::filterType::Sobel));
    comboBoxFilters->addItem(CFilter::typeToString(CFilter::filterType::Gaussian));
    comboBoxFilters->addItem(CFilter::typeToString(CFilter::filterType::Laplacian));

    comboBoxWindow1->addItem("Unchanged frame");
    comboBoxWindow2->addItem("Unchanged frame");


    listWidgetUsedFilters = new QListWidget();
    listWidgetUsedFilters->setMovement(QListView::Static);
    listWidgetUsedFilters->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listWidgetUsedFilters->setSelectionMode(QAbstractItemView::SingleSelection);

    lastUsedFilterIndex = -1;

    mainLayout->addWidget(camsFrame);
    mainLayout->addLayout(optionsLayout);

    optionsLayout->addWidget(firstOptionsFrame);
    optionsLayout->addWidget(secondOptionsFrame);

    camsLayout->addWidget(labelCamWindow1,0,0);
    camsLayout->addWidget(comboBoxWindow1,1,0);
    camsLayout->addWidget(labelCamWindow2,0,1);
    camsLayout->addWidget(comboBoxWindow2,1,1);

    firstOptionsLayout->addWidget(buttonCam,0,0);
    firstOptionsLayout->addWidget(lineEditCamID,0,1);
    firstOptionsLayout->addWidget(labelStatus,1,1);
    firstOptionsLayout->addWidget(buttonLoadImage,1,0);
    firstOptionsLayout->addWidget(labelFilters,2,0);
    firstOptionsLayout->addWidget(comboBoxFilters,2,1);
    firstOptionsLayout->addWidget(buttonAddFilter,3,0);
    firstOptionsLayout->addWidget(buttonRemoveFilter,3,1);
    firstOptionsLayout->addWidget(labelUsedFilters,0,2);

    firstOptionsLayout->addWidget(listWidgetUsedFilters,1,2,4,1);

    timer = new QTimer(this);
    timer->start(500);
    connectSignals();
}

MainWindow::~MainWindow()
{

}

QImage MainWindow::Mat2QImage(cv::Mat & src)
{
     cv::Mat temp; // make the same cv::Mat
     cvtColor(src, temp,cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy, see documentation
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     return dest;
}

void MainWindow::connectSignals()
{
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    connect(buttonCam, &QPushButton::released, this, &MainWindow::onReleased_buttonCam);
    connect(buttonLoadImage, &QPushButton::released, this, &MainWindow::onReleased_buttonLoadImage);
    connect(buttonAddFilter, &QPushButton::released, this, &MainWindow::onReleased_buttonAddFilter);
    connect(buttonRemoveFilter, &QPushButton::released, this, &MainWindow::onReleased_buttonRemoveFilter);
    connect(comboBoxWindow1, SIGNAL(currentIndexChanged(int)), this, SLOT(onChanged_comboBoxWindow1(int)));
    connect(comboBoxWindow2, SIGNAL(currentIndexChanged(int)), this, SLOT(onChanged_comboBoxWindow2(int)));
    connect(listWidgetUsedFilters, SIGNAL(currentRowChanged(int)), this, SLOT(onChanged_usedFilter(int)));
}

void MainWindow::update()
{
    // DODAC WYJATEK DLA imgHandler.isImageLoaded()
    // ODSWIEZAC TYLKO PRZY DODANIU FILTRU LUB ZMIANIE PARAMETROW

    if(imgHandler.isCamOpened() || imgHandler.isImageLoaded())
    {
        labelStatus->setText("Opened");
        QImage frame1, frame2;
        cv::Mat cvFrame;
        imgHandler.updateObject();
        imgHandler.getFrame1().copyTo(cvFrame); //kopiowanie obrazu - SLABOOOOO
        frame1 = Mat2QImage(cvFrame);
        imgHandler.getFrame2().copyTo(cvFrame); //kopiowanie obrazu - SLABOOOOO
        frame2 = Mat2QImage(cvFrame);
        labelCamWindow1->setPixmap(QPixmap::fromImage(frame1));
        labelCamWindow2->setPixmap(QPixmap::fromImage(frame2));
    }
    else
    {
       labelStatus->setText("Closed");
    }
}

void MainWindow::removeFilter(unsigned int index)
{
    imgHandler.removeFilter(index);

    comboBoxWindow1->removeItem(index+1);   // +1, bo zawsze jest Unchanged Frame na index = 0
    comboBoxWindow2->removeItem(index+1);

    QListWidgetItem *indexToRemove = listWidgetUsedFilters->takeItem(index);
    delete indexToRemove;
    QWidget *widgetToDelete = filterWidgetList.takeAt(index);
    delete widgetToDelete;

}

void MainWindow::onReleased_buttonCam()
{
    if(imgHandler.isCamOpened())
    {
        imgHandler.releaseCam();
        buttonCam->setText("Open Cam");
    }
    else
    {
        QString camID = lineEditCamID->text();
        imgHandler.openCam(camID.toInt());
        buttonCam->setText("Close Cam");
    }
}

void MainWindow::onReleased_buttonLoadImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

    if(fileName.isEmpty())
        return;

    if(imgHandler.isCamOpened())
    {
        imgHandler.releaseCam();
    }

    imgHandler.openImage(fileName);

}

void MainWindow::onReleased_buttonAddFilter()
{   
    QString chosenFilterName = comboBoxFilters->currentText();
    CFilter::filterType chosenFilterType = CFilter::stringToType(chosenFilterName);
    CFilterWidget *filterWidget = new CFilterWidget(chosenFilterType);


    imgHandler.addFilter(filterWidget->getFilterPtr());

    listWidgetUsedFilters->addItem(chosenFilterName);

    comboBoxWindow1->addItem(chosenFilterName);
    comboBoxWindow2->addItem(chosenFilterName);

    filterWidgetList.append(filterWidget);
    filterWidget->hide();

    secondOptionsLayout->addWidget(filterWidget);

    selectLastUsedFilterIndex();
}

void MainWindow::onReleased_buttonRemoveFilter()
{
    if(listWidgetUsedFilters->count() > 0)
    {
        removeFilter(listWidgetUsedFilters->currentRow());
        selectLastUsedFilterIndex();
    }
}

void MainWindow::onChanged_comboBoxWindow1(int index)
{
    imgHandler.setKeptFrame1(index);
}

void MainWindow::onChanged_comboBoxWindow2(int index)
{
    imgHandler.setKeptFrame2(index);
}

void MainWindow::onChanged_usedFilter(int index)
{
    if(index < 0)
    {
        return;
    }

    if(lastUsedFilterIndex >= 0)
        filterWidgetList.at(lastUsedFilterIndex)->hide();

    lastUsedFilterIndex = index;
    filterWidgetList.at(lastUsedFilterIndex)->show();

}

void MainWindow::selectLastUsedFilterIndex()
{
    int indexCount = listWidgetUsedFilters->count();
    if(indexCount >= 0)
    {
        listWidgetUsedFilters->setCurrentRow(indexCount-1);
        lastUsedFilterIndex = indexCount-1;
    }
    else
        lastUsedFilterIndex = -1;
}
