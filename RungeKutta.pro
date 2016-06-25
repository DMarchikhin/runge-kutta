#-------------------------------------------------
#
# Project created by QtCreator 2016-05-31T20:01:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = testtest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    differential-equation.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    differential-equation.h

FORMS    += mainwindow.ui
