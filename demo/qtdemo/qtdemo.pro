QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = qtdemo
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off
RESOURCES   += main.qrc

SOURCES     += main.cpp
SOURCES     += frmqtdemo.cpp
HEADERS     += frmqtdemo.h
FORMS       += frmqtdemo.ui

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/qtdemo
include ($$PWD/qtdemo/qtdemo.pri)
