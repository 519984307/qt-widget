QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = custompie
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcustompie.cpp
SOURCES     += custompie.cpp

HEADERS     += frmcustompie.h
HEADERS     += custompie.h

FORMS       += frmcustompie.ui
