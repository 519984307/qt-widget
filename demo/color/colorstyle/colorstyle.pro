QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = colorstyle
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcolorstyle.cpp
SOURCES     += colorstyle.cpp

HEADERS     += frmcolorstyle.h
HEADERS     += colorstyle.h

FORMS       += frmcolorstyle.ui

RESOURCES   += main.qrc
