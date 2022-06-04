QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = imageanimation
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmimageanimation.cpp
SOURCES     += imageanimation.cpp

HEADERS     += frmimageanimation.h
HEADERS     += imageanimation.h

FORMS       += frmimageanimation.ui

RESOURCES   += main.qrc
