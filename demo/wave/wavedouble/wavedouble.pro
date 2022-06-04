QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = wavedouble
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmwavedouble.cpp
SOURCES     += wavedouble.cpp

HEADERS     += frmwavedouble.h
HEADERS     += wavedouble.h

FORMS       += frmwavedouble.ui
