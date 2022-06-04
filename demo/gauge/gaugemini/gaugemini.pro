QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugemini
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugemini.cpp
SOURCES     += gaugemini.cpp

HEADERS     += frmgaugemini.h
HEADERS     += gaugemini.h

FORMS       += frmgaugemini.ui
