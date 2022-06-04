QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugeedit
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugeedit.cpp
SOURCES     += gaugeedit.cpp

HEADERS     += frmgaugeedit.h
HEADERS     += gaugeedit.h

FORMS       += frmgaugeedit.ui
