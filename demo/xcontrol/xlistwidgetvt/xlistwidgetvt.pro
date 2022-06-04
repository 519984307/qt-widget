QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = xlistwidgetvt
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += xlistwidgetvt.cpp
SOURCES     += frmxlistwidgetvt.cpp
HEADERS     += frmxlistwidgetvt.h
HEADERS     += xlistwidgetvt.h
FORMS       += frmxlistwidgetvt.ui
