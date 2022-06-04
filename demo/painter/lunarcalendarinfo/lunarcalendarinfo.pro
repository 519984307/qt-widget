QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = lunarcalendarinfo
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmlunarcalendarinfo.cpp
SOURCES     += lunarcalendarinfo.cpp

HEADERS     += frmlunarcalendarinfo.h
HEADERS     += lunarcalendarinfo.h

FORMS       += frmlunarcalendarinfo.ui
