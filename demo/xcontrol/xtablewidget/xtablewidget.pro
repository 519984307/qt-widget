QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = xtablewidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmxtablewidget.cpp
SOURCES     += xtablewidget.cpp

HEADERS     += frmxtablewidget.h
HEADERS     += xtablewidget.h

FORMS       += frmxtablewidget.ui
