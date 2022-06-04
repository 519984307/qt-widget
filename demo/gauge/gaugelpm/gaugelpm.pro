QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugelpm
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugelpm.cpp
SOURCES     += gaugelpm.cpp

HEADERS     += frmgaugelpm.h
HEADERS     += gaugelpm.h

FORMS       += frmgaugelpm.ui
