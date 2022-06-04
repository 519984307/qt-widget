QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = customdart
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcustomdart.cpp
SOURCES     += customdart.cpp

HEADERS     += frmcustomdart.h
HEADERS     += customdart.h

FORMS       += frmcustomdart.ui
