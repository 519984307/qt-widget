QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = lednumber
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmlednumber.cpp
SOURCES     += lednumber.cpp

HEADERS     += frmlednumber.h
HEADERS     += lednumber.h

FORMS       += frmlednumber.ui
