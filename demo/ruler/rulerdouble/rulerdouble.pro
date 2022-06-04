QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = rulerdouble
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmrulerdouble.cpp
SOURCES     += rulerdouble.cpp

HEADERS     += frmrulerdouble.h
HEADERS     += rulerdouble.h

FORMS       += frmrulerdouble.ui
