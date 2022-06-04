QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = magicpenguin
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmmagicpenguin.cpp
SOURCES     += magicpenguin.cpp

HEADERS     += frmmagicpenguin.h
HEADERS     += magicpenguin.h

FORMS       += frmmagicpenguin.ui
