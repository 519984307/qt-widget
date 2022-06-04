QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = magicpool
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += magicpool.cpp
SOURCES     += frmmagicpool.cpp

HEADERS     += magicpool.h
HEADERS     += frmmagicpool.h

FORMS       += frmmagicpool.ui
