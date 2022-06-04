QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = scantantan
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmscantantan.cpp
SOURCES     += scantantan.cpp

HEADERS     += frmscantantan.h
HEADERS     += scantantan.h

FORMS       += frmscantantan.ui

RESOURCES   += main.qrc
