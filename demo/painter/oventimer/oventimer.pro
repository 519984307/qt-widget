QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = oventimer
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmoventimer.cpp
SOURCES     += oventimer.cpp

HEADERS     += frmoventimer.h
HEADERS     += oventimer.h

FORMS       += frmoventimer.ui
