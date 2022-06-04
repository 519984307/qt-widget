QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = customgraphics
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcustomgraphics.cpp
SOURCES     += customgraphics.cpp

HEADERS     += frmcustomgraphics.h
HEADERS     += customgraphics.h

FORMS       += frmcustomgraphics.ui
