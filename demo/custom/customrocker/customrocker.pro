QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = customrocker
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcustomrocker.cpp
SOURCES     += customrocker.cpp

HEADERS     += frmcustomrocker.h
HEADERS     += customrocker.h

FORMS       += frmcustomrocker.ui
