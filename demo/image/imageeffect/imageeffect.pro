QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = imageeffect
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmimageeffect.cpp
SOURCES     += imageeffect.cpp

HEADERS     += frmimageeffect.h
HEADERS     += imageeffect.h

FORMS       += frmimageeffect.ui

RESOURCES   += main.qrc
