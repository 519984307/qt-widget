QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = flowlayout
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmflowlayout.cpp
SOURCES     += flowlayout.cpp

HEADERS     += frmflowlayout.h
HEADERS     += flowlayout.h

FORMS       += frmflowlayout.ui
