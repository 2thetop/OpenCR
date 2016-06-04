#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T08:42:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCR_FW_Downloader
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    qextserial/qextserialenumerator.cpp \
    qextserial/qextserialenumerator_linux.cpp \
    qextserial/qextserialenumerator_osx.cpp \
    qextserial/qextserialenumerator_unix.cpp \
    qextserial/qextserialenumerator_win.cpp \
    qextserial/qextserialport.cpp \
    qextserial/qextserialport_unix.cpp \
    qextserial/qextserialport_win.cpp

HEADERS  += dialog.h \
    qextserial/qextserialenumerator.h \
    qextserial/qextserialenumerator_p.h \
    qextserial/qextserialport.h \
    qextserial/qextserialport_global.h \
    qextserial/qextserialport_p.h

FORMS    += dialog.ui
