#-------------------------------------------------
#
# Project created by QtCreator 2016-10-02T19:10:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Othello
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    boardlabel.cpp

HEADERS  += dialog.h \
    boardlabel.h

FORMS    += dialog.ui

RESOURCES += \
    MyResource.qrc
