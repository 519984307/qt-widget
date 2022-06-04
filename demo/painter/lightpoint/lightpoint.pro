QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = lightpoint
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off
RESOURCES   += main.qrc

SOURCES     += main.cpp
SOURCES     += frmlightpoint.cpp
SOURCES     += lightpoint.cpp

HEADERS     += frmlightpoint.h
HEADERS     += lightpoint.h

FORMS       += frmlightpoint.ui
