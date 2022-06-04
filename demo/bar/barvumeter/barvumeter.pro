QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = barvumeter
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmbarvumeter.cpp
SOURCES     += barvumeter.cpp

HEADERS     += frmbarvumeter.h
HEADERS     += barvumeter.h

FORMS       += frmbarvumeter.ui
