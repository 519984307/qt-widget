QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = colorpanelhsb
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcolorpanelhsb.cpp
SOURCES     += colorpanelbar.cpp
SOURCES     += colorpanelhsb.cpp

HEADERS     += frmcolorpanelhsb.h
HEADERS     += colorpanelbar.h
HEADERS     += colorpanelhsb.h

FORMS       += frmcolorpanelhsb.ui
