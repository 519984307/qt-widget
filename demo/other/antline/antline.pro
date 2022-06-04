QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = antline
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmantline.cpp
SOURCES     += antline.cpp

HEADERS     += frmantline.h
HEADERS     += antline.h

FORMS       += frmantline.ui
