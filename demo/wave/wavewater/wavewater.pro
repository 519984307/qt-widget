QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = wavewater
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmwavewater.cpp
SOURCES     += wavewater.cpp

HEADERS     += frmwavewater.h
HEADERS     += wavewater.h

FORMS       += frmwavewater.ui

RESOURCES   += main.qrc
