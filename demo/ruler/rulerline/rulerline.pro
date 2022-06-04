QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = rulerline
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmrulerline.cpp
SOURCES     += rulerline.cpp

HEADERS     += frmrulerline.h
HEADERS     += rulerline.h

FORMS       += frmrulerline.ui
