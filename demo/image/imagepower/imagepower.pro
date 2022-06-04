QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = imagepower
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmimagepower.cpp
SOURCES     += imagepower.cpp

HEADERS     += frmimagepower.h
HEADERS     += imagepower.h

FORMS       += frmimagepower.ui

RESOURCES   += main.qrc
