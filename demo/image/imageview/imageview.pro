QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = imageview
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmimageview.cpp
SOURCES     += imageview.cpp

HEADERS     += frmimageview.h
HEADERS     += imageview.h

FORMS       += frmimageview.ui

RESOURCES   += main.qrc
