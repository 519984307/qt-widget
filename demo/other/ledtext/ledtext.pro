QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = ledtext
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmledtext.cpp
SOURCES     += ledtext.cpp

HEADERS     += frmledtext.h
HEADERS     += ledtext.h

FORMS       += frmledtext.ui
