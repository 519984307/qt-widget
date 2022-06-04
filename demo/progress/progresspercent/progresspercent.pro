QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = progresspercent
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogresspercent.cpp
SOURCES     += progresspercent.cpp

HEADERS     += frmprogresspercent.h
HEADERS     += progresspercent.h

FORMS       += frmprogresspercent.ui

RESOURCES   += main.qrc
