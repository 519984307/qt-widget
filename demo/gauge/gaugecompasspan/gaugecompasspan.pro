QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugecompasspan
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugecompasspan.cpp
SOURCES     += gaugecompasspan.cpp

HEADERS     += frmgaugecompasspan.h
HEADERS     += gaugecompasspan.h

FORMS       += frmgaugecompasspan.ui
