QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = shadowwidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmshadowwidget.cpp
SOURCES     += shadowwidget.cpp

HEADERS     += frmshadowwidget.h
HEADERS     += shadowwidget.h

FORMS       += frmshadowwidget.ui
