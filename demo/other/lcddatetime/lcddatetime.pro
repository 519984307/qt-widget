QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = lcddatetime
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmlcddatetime.cpp
SOURCES     += lcddatetime.cpp

HEADERS     += frmlcddatetime.h
HEADERS     += lcddatetime.h

FORMS       += frmlcddatetime.ui
