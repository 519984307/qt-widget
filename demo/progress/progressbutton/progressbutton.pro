QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = progressbutton
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogressbutton.cpp
SOURCES     += progressbutton.cpp

HEADERS     += frmprogressbutton.h
HEADERS     += progressbutton.h

FORMS       += frmprogressbutton.ui
