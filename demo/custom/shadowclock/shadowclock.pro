QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = shadowclock
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmshadowclock.cpp
SOURCES     += shadowclock.cpp

HEADERS     += frmshadowclock.h
HEADERS     += shadowclock.h

FORMS       += frmshadowclock.ui
