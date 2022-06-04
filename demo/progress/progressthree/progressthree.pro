QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = progressthree
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogressthree.cpp
SOURCES     += progressthree.cpp

HEADERS     += frmprogressthree.h
HEADERS     += progressthree.h

FORMS       += frmprogressthree.ui
