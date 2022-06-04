QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugeround
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugeround.cpp
SOURCES     += gaugeround.cpp

HEADERS     += frmgaugeround.h
HEADERS     += gaugeround.h

FORMS       += frmgaugeround.ui
