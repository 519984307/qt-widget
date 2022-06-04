QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = colorcombobox
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcolorcombobox.cpp
SOURCES     += colorcombobox.cpp

HEADERS     += frmcolorcombobox.h
HEADERS     += colorcombobox.h

FORMS       += frmcolorcombobox.ui
