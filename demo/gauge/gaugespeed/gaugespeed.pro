QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugespeed
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugespeed.cpp
SOURCES     += gaugespeed.cpp

HEADERS     += frmgaugespeed.h
HEADERS     += gaugespeed.h

FORMS       += frmgaugespeed.ui

RESOURCES   += main.qrc
