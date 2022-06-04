QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = lcdnumber
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmlcdnumber.cpp
SOURCES     += lcdnumber.cpp

HEADERS     += frmlcdnumber.h
HEADERS     += lcdnumber.h

FORMS       += frmlcdnumber.ui
