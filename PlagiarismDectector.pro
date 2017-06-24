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
    detector.cpp \
    file.cpp \
    project.cpp \
    plagiarism_detector_widget.cpp \
    costflow_alg.cpp \
    detector_file.cpp \
    strategies_file.cpp \
    detector_project.cpp \
    strategies_project.cpp \
    monitor.cpp

HEADERS  += \
    file.h \
    project.h \
    detector.h \
    plagiarism_detector_widget.h \
    costflow_alg.h \
    detector_project.h \
    detector_file.h \
    strategies_file.h \
    strategies_project.h \
    monitor.h

DEFINES += QT_WIDGET
