QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = switchbutton
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmswitchbutton.cpp
SOURCES     += switchbutton.cpp

HEADERS     += frmswitchbutton.h
HEADERS     += switchbutton.h

FORMS       += frmswitchbutton.ui
