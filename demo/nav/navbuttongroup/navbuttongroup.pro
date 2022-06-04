QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = navbuttongroup
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmnavbuttongroup.cpp
SOURCES     += navbuttongroup.cpp

HEADERS     += frmnavbuttongroup.h
HEADERS     += navbuttongroup.h

FORMS       += frmnavbuttongroup.ui
