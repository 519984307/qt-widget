QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = wavechart
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmwavechart.cpp
SOURCES     += smoothcurve.cpp
SOURCES     += wavechart.cpp

HEADERS     += frmwavechart.h
HEADERS     += smoothcurve.h
HEADERS     += wavechart.h

FORMS       += frmwavechart.ui
