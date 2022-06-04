QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = xlistwidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += xlistwidget.cpp
SOURCES     += iconhelper.cpp
SOURCES     += frmxlistwidget.cpp
HEADERS     += frmxlistwidget.h
HEADERS     += xlistwidget.h
HEADERS     += iconhelper.h
FORMS       += frmxlistwidget.ui
RESOURCES   += main.qrc
