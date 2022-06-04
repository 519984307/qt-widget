QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugesimple
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugesimple.cpp
SOURCES     += gaugesimple.cpp

HEADERS     += frmgaugesimple.h
HEADERS     += gaugesimple.h

FORMS       += frmgaugesimple.ui
