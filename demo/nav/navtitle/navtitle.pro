QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = navtitle
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmnavtitle.cpp
SOURCES     += navtitle.cpp

HEADERS     += frmnavtitle.h
HEADERS     += navtitle.h

FORMS       += frmnavtitle.ui

RESOURCES   += main.qrc
