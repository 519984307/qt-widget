QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugecircle
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += gaugecircle.cpp
SOURCES     += frmgaugecircle.cpp

HEADERS     += gaugecircle.h
HEADERS     += frmgaugecircle.h

FORMS       += frmgaugecircle.ui
