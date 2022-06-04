QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = progressround
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogressround.cpp
SOURCES     += progressround.cpp

HEADERS     += frmprogressround.h
HEADERS     += progressround.h

FORMS       += frmprogressround.ui
