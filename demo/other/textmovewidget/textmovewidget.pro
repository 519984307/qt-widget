QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = textmovewidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmtextmovewidget.cpp
SOURCES     += textmovewidget.cpp

HEADERS     += frmtextmovewidget.h
HEADERS     += textmovewidget.h

FORMS       += frmtextmovewidget.ui
