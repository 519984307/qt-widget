QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = timeline
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmtimeline.cpp
SOURCES     += timeline.cpp

HEADERS     += frmtimeline.h
HEADERS     += timeline.h

FORMS       += frmtimeline.ui
