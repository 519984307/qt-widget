QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = magicfish
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += magicfish.cpp
SOURCES     += frmmagicfish.cpp

HEADERS     += magicfish.h
HEADERS     += frmmagicfish.h

FORMS       += frmmagicfish.ui
