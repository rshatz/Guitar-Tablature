#-------------------------------------------------
#
# Project created by QtCreator 2015-10-30T06:07:34
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Guitar-Tablature
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tabarea.cpp \
    fretboard.cpp

HEADERS  += mainwindow.h \
    tabarea.h \
    fretboard.h

RESOURCES += \
    guitar-tablature.qrc

DISTFILES +=
