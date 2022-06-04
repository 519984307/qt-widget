QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = magicmouse
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmmagicmouse.cpp
SOURCES     += magicmouse.cpp

HEADERS     += frmmagicmouse.h
HEADERS     += magicmouse.h

FORMS       += frmmagicmouse.ui
