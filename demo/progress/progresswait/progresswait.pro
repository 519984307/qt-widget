QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = progresswait
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogresswait.cpp
SOURCES     += progresswait.cpp

HEADERS     += frmprogresswait.h
HEADERS     += progresswait.h

FORMS       += frmprogresswait.ui
