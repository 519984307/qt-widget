QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugedial
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugedial.cpp
SOURCES     += gaugedial.cpp

HEADERS     += frmgaugedial.h
HEADERS     += gaugedial.h

FORMS       += frmgaugedial.ui
