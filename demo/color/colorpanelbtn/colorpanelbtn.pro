QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = colorpanelbtn
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcolorpanelbtn.cpp
SOURCES     += colorpanelbtn.cpp

HEADERS     += frmcolorpanelbtn.h
HEADERS     += colorpanelbtn.h

FORMS       += frmcolorpanelbtn.ui
