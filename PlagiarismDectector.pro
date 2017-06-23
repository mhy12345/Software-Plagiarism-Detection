#-------------------------------------------------
#
# Project created by QtCreator 2017-06-23T15:13:22
#
#-------------------------------------------------

QT       += core gui

CONFIG   += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlagiarismDectector
TEMPLATE = app


SOURCES += main.cpp\
        plagiarismdetectorwidget.cpp \
    detector.cpp \
    cost_flow.cpp \
    file.cpp \
    project.cpp \
    projectdetectormonitor.cpp

HEADERS  += plagiarismdetectorwidget.h \
    cost_flow.h \
    file.h \
    project.h \
    detectors.h \
    projectdetectormonitor.h
