QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = combobox
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmxcombobox.cpp
SOURCES     += xcombobox.cpp

HEADERS     += frmxcombobox.h
HEADERS     += xcombobox.h

FORMS       += frmxcombobox.ui
