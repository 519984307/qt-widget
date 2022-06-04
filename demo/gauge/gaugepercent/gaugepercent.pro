QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugepercent
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugepercent.cpp
SOURCES     += gaugepercent.cpp

HEADERS     += frmgaugepercent.h
HEADERS     += gaugepercent.h

FORMS       += frmgaugepercent.ui

RESOURCES   += main.qrc
