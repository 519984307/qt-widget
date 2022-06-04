QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = adswidget2
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmadswidget2.cpp
SOURCES     += adswidget2.cpp

HEADERS     += frmadswidget2.h
HEADERS     += adswidget2.h

FORMS       += frmadswidget2.ui

RESOURCES   += main.qrc
