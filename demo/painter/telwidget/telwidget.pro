QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = telwidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off
RESOURCES   += main.qrc

SOURCES     += main.cpp
SOURCES     += zhtopy.cpp
SOURCES     += telwidget.cpp
SOURCES     += frmtelwidget.cpp

HEADERS     += telwidget.h
HEADERS     += zhtopy.h
HEADERS     += frmtelwidget.h

FORMS       += frmtelwidget.ui
