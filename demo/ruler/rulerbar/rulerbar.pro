QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = rulerbar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmrulerbar.cpp
SOURCES     += rulerbar.cpp

HEADERS     += frmrulerbar.h
HEADERS     += rulerbar.h

FORMS       += frmrulerbar.ui
