QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = shadowcalendar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmshadowcalendar.cpp
SOURCES     += shadowcalendar.cpp

HEADERS     += frmshadowcalendar.h
HEADERS     += shadowcalendar.h

FORMS       += frmshadowcalendar.ui

RESOURCES   += main.qrc
