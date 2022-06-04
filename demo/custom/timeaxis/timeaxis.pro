QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = timeaxis
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmtimeaxis.cpp
SOURCES     += timeaxis.cpp

HEADERS     += frmtimeaxis.h
HEADERS     += timeaxis.h

FORMS       += frmtimeaxis.ui
