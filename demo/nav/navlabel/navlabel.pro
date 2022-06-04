QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = navlabel
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmnavlabel.cpp
SOURCES     += navlabel.cpp

HEADERS     += frmnavlabel.h
HEADERS     += navlabel.h

FORMS       += frmnavlabel.ui
