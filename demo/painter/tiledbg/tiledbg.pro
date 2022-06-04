QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = tiledbg
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmtiledbg.cpp
SOURCES     += tiledbg.cpp

HEADERS     += frmtiledbg.h
HEADERS     += tiledbg.h

FORMS       += frmtiledbg.ui
