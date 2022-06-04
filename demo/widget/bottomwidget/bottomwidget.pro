QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = bottomwidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmbottomwidget.cpp
SOURCES     += bottomwidget.cpp

HEADERS     += frmbottomwidget.h
HEADERS     += bottomwidget.h

FORMS       += frmbottomwidget.ui

INCLUDEPATH += $$PWD
