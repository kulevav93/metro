#-------------------------------------------------
#
# Project created by QtCreator 2022-11-10T15:41:40
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Metro
TEMPLATE = app


SOURCES += main.cpp\
        metromap.cpp \
    metroplot.cpp \
    station.cpp \
    transferstation.cpp \
    line.cpp

HEADERS  += metromap.h \
    metroplot.h \
    station.h \
    transferstation.h \
    line.h
