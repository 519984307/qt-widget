QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = customring
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcustomring.cpp
SOURCES     += customring.cpp

HEADERS     += frmcustomring.h
HEADERS     += customring.h

FORMS       += frmcustomring.ui
