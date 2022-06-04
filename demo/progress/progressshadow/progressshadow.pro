QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = progressshadow
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogressshadow.cpp
SOURCES     += progressshadow.cpp

HEADERS     += frmprogressshadow.h
HEADERS     += progressshadow.h

FORMS       += frmprogressshadow.ui
