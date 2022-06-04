QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugecompass2
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugecompass2.cpp
SOURCES     += gaugecompass2.cpp

HEADERS     += frmgaugecompass2.h
HEADERS     += gaugecompass2.h

FORMS       += frmgaugecompass2.ui
