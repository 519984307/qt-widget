QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = progresscountdown
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogresscountdown.cpp
SOURCES     += progresscountdown.cpp

HEADERS     += frmprogresscountdown.h
HEADERS     += progresscountdown.h

FORMS       += frmprogresscountdown.ui
