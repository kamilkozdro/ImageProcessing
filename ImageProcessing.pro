QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cfilter.cpp \
    cfilterwidget.cpp \
    cimagecamerasource.cpp \
    cimagefilesource.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CImageSource.h \
    CMessageBox.h \
    cfilter.h \
    cfilterwidget.h \
    cimagecamerasource.h \
    cimagefilesource.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# --------------------------
# Debug version libraries:

win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Library/opencv/build/x64/vc16/lib/ -lopencv_world490d

win32:CONFIG(debug, debug|release): INCLUDEPATH += $$PWD/../../../Library/opencv/build/include
win32:CONFIG(debug, debug|release): DEPENDPATH += $$PWD/../../../Library/opencv/build/include

# --------------------------
# Release version libraries:

win32:CONFIG(release, debug|release):  LIBS += -L$$PWD/../../../Library/opencv-4.10.0-img-process-build/install/x64/vc17/lib/ -lopencv_core4100
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Library/opencv-4.10.0-img-process-build/install/x64/vc17/lib/ -lopencv_highgui4100
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Library/opencv-4.10.0-img-process-build/install/x64/vc17/lib/ -lopencv_imgcodecs4100
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Library/opencv-4.10.0-img-process-build/install/x64/vc17/lib/ -lopencv_imgproc4100
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Library/opencv-4.10.0-img-process-build/install/x64/vc17/lib/ -lopencv_videoio4100

win32:CONFIG(release, debug|release): INCLUDEPATH += $$PWD/../../../Library/opencv-4.10.0-img-process-build/install/include
win32:CONFIG(release, debug|release): DEPENDPATH += $$PWD/../../../Library/opencv-4.10.0-img-process-build/install/include
