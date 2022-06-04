QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = panelmovewidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmpanelmovewidget.cpp
SOURCES     += lightbutton.cpp

HEADERS     += frmpanelmovewidget.h
HEADERS     += lightbutton.h

FORMS       += frmpanelmovewidget.ui
