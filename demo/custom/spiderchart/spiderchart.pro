QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = spiderchart
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmspiderchart.cpp
SOURCES     += spiderchart.cpp

HEADERS     += frmspiderchart.h
HEADERS     += spiderchart.h

FORMS       += frmspiderchart.ui
