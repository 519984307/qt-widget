QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = waveplot
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmwaveplot.cpp
SOURCES     += waveplot.cpp

HEADERS     += frmwaveplot.h
HEADERS     += waveplot.h

FORMS       += frmwaveplot.ui
