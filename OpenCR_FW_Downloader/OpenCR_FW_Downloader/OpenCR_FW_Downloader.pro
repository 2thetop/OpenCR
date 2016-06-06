#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T08:42:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCR_FW_Downloader
TEMPLATE = app

include(./qextserialport/qextserialport.pri)

SOURCES += main.cpp\
        dialog.cpp \
    hled.cpp


HEADERS  += dialog.h \
    hled.h


FORMS    += dialog.ui

