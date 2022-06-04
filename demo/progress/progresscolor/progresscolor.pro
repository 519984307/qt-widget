QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = progresscolor
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogresscolor.cpp
SOURCES     += progresscolor.cpp

HEADERS     += frmprogresscolor.h
HEADERS     += progresscolor.h

FORMS       += frmprogresscolor.ui
