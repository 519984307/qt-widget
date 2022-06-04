QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = wavedata
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmwavedata.cpp
SOURCES     += smoothcurve.cpp
SOURCES     += wavedata.cpp

HEADERS     += frmwavedata.h
HEADERS     += smoothcurve.h
HEADERS     += wavedata.h

FORMS       += frmwavedata.ui
RESOURCES   += main.qrc
