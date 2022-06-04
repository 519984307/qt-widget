QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = iconeditor
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmiconeditor.cpp
SOURCES     += iconeditor.cpp

HEADERS     += frmiconeditor.h
HEADERS     += iconeditor.h

FORMS       += frmiconeditor.ui
