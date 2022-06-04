QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = imageclock
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmimageclock.cpp
SOURCES     += imageclock.cpp

HEADERS     += frmimageclock.h
HEADERS     += imageclock.h

FORMS       += frmimageclock.ui

RESOURCES   += main.qrc
