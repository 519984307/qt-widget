QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugewatch
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugewatch.cpp
SOURCES     += gaugewatch.cpp

HEADERS     += frmgaugewatch.h
HEADERS     += gaugewatch.h

FORMS       += frmgaugewatch.ui
