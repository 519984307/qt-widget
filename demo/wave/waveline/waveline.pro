QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = waveline
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmwaveline.cpp
SOURCES     += waveline.cpp

HEADERS     += frmwaveline.h
HEADERS     += waveline.h

FORMS       += frmwaveline.ui
