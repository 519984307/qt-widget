QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
lessThan(QT_MAJOR_VERSION, 5): QT += script

TARGET      = weather
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmweather.cpp
SOURCES     += weather.cpp
SOURCES     += cityhelper.cpp

HEADERS     += frmweather.h
HEADERS     += weather.h
HEADERS     += cityhelper.h

FORMS       += frmweather.ui

RESOURCES   += main.qrc
