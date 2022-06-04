QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = xprogressbar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmxprogressbar.cpp
SOURCES     += xprogressbar.cpp

HEADERS     += frmxprogressbar.h
HEADERS     += xprogressbar.h

FORMS       += frmxprogressbar.ui
