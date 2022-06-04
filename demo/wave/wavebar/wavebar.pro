QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = wavebar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmwavebar.cpp
SOURCES     += wavebar.cpp

HEADERS     += frmwavebar.h
HEADERS     += wavebar.h

FORMS       += frmwavebar.ui
