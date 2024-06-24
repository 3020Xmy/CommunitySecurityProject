QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    communitysecurityserver.cpp \
    srcFile/detection.cpp \
    srcFile/sql.cpp \
    uiFile/registerwidget.cpp \
    uiFile/seletewidget.cpp

HEADERS += \
    communitysecurityserver.h \
    srcFile/detection.h \
    srcFile/sql.h \
    uiFile/registerwidget.h \
    uiFile/seletewidget.h

FORMS += \
    communitysecurityserver.ui \
    uiFile/registerwidget.ui \
    uiFile/seletewidget.ui

#添加opencv，seetaface头文件
INCLUDEPATH += /home/wildpointer/opencv4-pc/include
INCLUDEPATH += /home/wildpointer/opencv4-pc/include/opencv4/opencv2
INCLUDEPATH += /home/wildpointer/opencv4-pc/include/opencv4
INCLUDEPATH += /home/wildpointer/opencv4-pc/include/seeta

#添加opencv，seetace的库
LIBS+=-L//home/wildpointer/opencv4-pc/lib -lopencv_world -lSeetaFaceDetector -lSeetaFaceLandmarker -lSeetaFaceRecognizer -lSeetaFaceTracker -lSeetaNet -lSeetaQualityAssessor

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
