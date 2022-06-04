QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = progressarc
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogressarc.cpp
SOURCES     += progressarc.cpp

HEADERS     += frmprogressarc.h
HEADERS     += progressarc.h

FORMS       += frmprogressarc.ui
