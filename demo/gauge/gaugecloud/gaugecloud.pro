QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugecloud
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugecloud.cpp
SOURCES     += gaugecloud.cpp

HEADERS     += frmgaugecloud.h
HEADERS     += gaugecloud.h

FORMS       += frmgaugecloud.ui

RESOURCES   += main.qrc
