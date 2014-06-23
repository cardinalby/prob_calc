#-------------------------------------------------
#
# Project created by QtCreator 2014-06-20T23:53:16
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = probability_calc
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    probability_util.cpp

QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

HEADERS += \
    probability_util.h
