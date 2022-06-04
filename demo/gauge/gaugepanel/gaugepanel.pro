QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugepanel
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugepanel.cpp
SOURCES     += gaugepanel.cpp

HEADERS     += frmgaugepanel.h
HEADERS     += gaugepanel.h

FORMS       += frmgaugepanel.ui

