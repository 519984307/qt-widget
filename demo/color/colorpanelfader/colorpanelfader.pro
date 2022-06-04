QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = colorpanelfader
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcolorpanelfader.cpp
SOURCES     += colorpanelfader.cpp
SOURCES     += colorpanelbar.cpp

HEADERS     += frmcolorpanelfader.h
HEADERS     += colorpanelfader.h
HEADERS     += colorpanelbar.h

FORMS       += frmcolorpanelfader.ui
