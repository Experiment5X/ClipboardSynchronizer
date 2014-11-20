#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T00:52:53
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClipboardSynchronizer
CONFIG += c++11
TEMPLATE = app


SOURCES += main.cpp\
    ClipboardSynchronizer.cpp \
    ClipboardData.cpp \
    QMimeType.cpp

HEADERS  += \
    ClipboardSynchronizer.h \
    ClipboardData.h \
    QMimeType.h
