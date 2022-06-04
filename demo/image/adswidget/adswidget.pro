QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = adswidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmadswidget.cpp
SOURCES     += adswidget.cpp

HEADERS     += frmadswidget.h
HEADERS     += adswidget.h

FORMS       += frmadswidget.ui

RESOURCES   += main.qrc
