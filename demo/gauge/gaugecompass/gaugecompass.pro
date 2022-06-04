QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugecompass
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugecompass.cpp
SOURCES     += gaugecompass.cpp

HEADERS     += frmgaugecompass.h
HEADERS     += gaugecompass.h

FORMS       += frmgaugecompass.ui
