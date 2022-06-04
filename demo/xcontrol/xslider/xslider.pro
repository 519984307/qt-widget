QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = xslider
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmxslider.cpp
SOURCES     += xslider.cpp

HEADERS     += frmxslider.h
HEADERS     += xslider.h

FORMS       += frmxslider.ui
