#-------------------------------------------------
#
# Project created by QtCreator 2017-04-29T14:24:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AVRmidi
TEMPLATE = app

QMAKE_CXXFLAGS += "-std=c++11"

win32|win64{
    RC_FILE=  index.rc
    OTHER_FILES+= index.rc
    DISTFILES += index.rc
}

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
