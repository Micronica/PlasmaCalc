QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = PlasmaCalc
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    Poisson.cpp \
    sden.cpp \
    sw.cpp \
    videoplayer.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    edgex.h \
    convect.h \
    dif3.h \
    edgey.h \
    givevalue.h \
    mean.h \
    sve.h \
    transvalue.h \
    videoplayer.h

FORMS    += mainwindow.ui \
    videoplayer.ui

DISTFILES += \
    PlasmaCalc.pro.user

RESOURCES += \
    icons.qrc

INCLUDEPATH += /usr/local/Cellar

LIBS += -L/usr/local/lib

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

