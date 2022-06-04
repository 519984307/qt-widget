QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = panelwidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmpanelitem.cpp
SOURCES     += panelitem.cpp

HEADERS     += frmpanelitem.h
HEADERS     += panelitem.h

FORMS       += frmpanelitem.ui
