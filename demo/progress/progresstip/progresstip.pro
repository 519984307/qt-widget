QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = progresstip
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogresstip.cpp
SOURCES     += progresstip.cpp

HEADERS     += frmprogresstip.h
HEADERS     += progresstip.h

FORMS       += frmprogresstip.ui
