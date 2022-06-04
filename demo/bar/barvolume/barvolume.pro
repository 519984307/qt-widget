QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = barvolume
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmbarvolume.cpp
SOURCES     += barvolume.cpp

HEADERS     += frmbarvolume.h
HEADERS     += barvolume.h

FORMS       += frmbarvolume.ui
