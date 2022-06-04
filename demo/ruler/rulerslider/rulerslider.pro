QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = rulerslider
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmrulerslider.cpp
SOURCES     += rulerslider.cpp

HEADERS     += frmrulerslider.h
HEADERS     += rulerslider.h

FORMS       += frmrulerslider.ui
