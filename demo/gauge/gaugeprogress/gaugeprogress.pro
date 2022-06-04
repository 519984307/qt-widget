QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugeprogress
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugeprogress.cpp
SOURCES     += gaugeprogress.cpp

HEADERS     += frmgaugeprogress.h
HEADERS     += gaugeprogress.h

FORMS       += frmgaugeprogress.ui
