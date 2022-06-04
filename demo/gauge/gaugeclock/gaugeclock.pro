QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugeclock
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugeclock.cpp
SOURCES     += gaugeclock.cpp

HEADERS     += frmgaugeclock.h
HEADERS     += gaugeclock.h

FORMS       += frmgaugeclock.ui
