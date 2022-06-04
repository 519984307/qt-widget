QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = selectwidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmselectwidget.cpp
SOURCES     += selectwidget.cpp

HEADERS     += frmselectwidget.h
HEADERS     += selectwidget.h

FORMS       += frmselectwidget.ui
