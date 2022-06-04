QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = videoplayback
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmvideoplayback.cpp
SOURCES     += videoplayback.cpp

HEADERS     += frmvideoplayback.h
HEADERS     += videoplayback.h

FORMS       += frmvideoplayback.ui
