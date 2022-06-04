QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = xstackwidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += xstackwidget.cpp
HEADERS     += xstackwidget.h

SOURCES     += frmxstackwidget.cpp
HEADERS     += frmxstackwidget.h
FORMS       += frmxstackwidget.ui
