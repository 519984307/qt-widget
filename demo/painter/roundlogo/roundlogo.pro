QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = roundlogo
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmroundlogo.cpp
SOURCES     += roundlogo.cpp

HEADERS     += frmroundlogo.h
HEADERS     += roundlogo.h

FORMS       += frmroundlogo.ui
