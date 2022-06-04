QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugecolor
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugecolor.cpp
SOURCES     += gaugecolor.cpp

HEADERS     += frmgaugecolor.h
HEADERS     += gaugecolor.h

FORMS       += frmgaugecolor.ui
