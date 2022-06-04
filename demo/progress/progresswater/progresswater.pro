QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = progresswater
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogresswater.cpp
SOURCES     += progresswater.cpp

HEADERS     += frmprogresswater.h
HEADERS     += progresswater.h

FORMS       += frmprogresswater.ui
