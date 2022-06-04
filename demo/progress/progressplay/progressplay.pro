QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = progressplay
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogressplay.cpp
SOURCES     += progressplay.cpp

HEADERS     += frmprogressplay.h
HEADERS     += progressplay.h

FORMS       += frmprogressplay.ui
