QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugeplane
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += gaugeplane.cpp
SOURCES     += frmgaugeplane.cpp

HEADERS     += frmgaugeplane.h
HEADERS     += gaugeplane.h

FORMS       += frmgaugeplane.ui
