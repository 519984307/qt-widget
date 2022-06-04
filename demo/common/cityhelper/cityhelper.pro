QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = cityhelper
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp

SOURCES     += frmcityhelper.cpp
SOURCES     += cityhelper.cpp

HEADERS     += frmcityhelper.h
HEADERS     += cityhelper.h

FORMS       += frmcityhelper.ui

RESOURCES   += main.qrc
