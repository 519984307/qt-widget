QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = squarelayout
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmsquarelayout.cpp
SOURCES     += squarelayout.cpp

HEADERS     += frmsquarelayout.h
HEADERS     += squarelayout.h

FORMS       += frmsquarelayout.ui
