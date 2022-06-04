QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = rulerscale
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmrulerscale.cpp
SOURCES     += rulerscale.cpp

HEADERS     += frmrulerscale.h
HEADERS     += rulerscale.h

FORMS       += frmrulerscale.ui
