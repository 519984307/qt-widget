QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = navpage
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off
RESOURCES   += main.qrc

SOURCES     += main.cpp
SOURCES     += frmnavpage.cpp
SOURCES     += navpage.cpp

HEADERS     += frmnavpage.h
HEADERS     += navpage.h

FORMS       += frmnavpage.ui
