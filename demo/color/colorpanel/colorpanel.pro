QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = colorpanel
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcolorpanel.cpp
SOURCES     += colorbutton.cpp
SOURCES     += colorpanelbtn.cpp
SOURCES     += colorpanelbar.cpp
SOURCES     += colorpanelhsb.cpp
SOURCES     += colorpanelfader.cpp

HEADERS     += frmcolorpanel.h
HEADERS     += colorbutton.h
HEADERS     += colorpanelbtn.h
HEADERS     += colorpanelbar.h
HEADERS     += colorpanelhsb.h
HEADERS     += colorpanelfader.h

FORMS       += frmcolorpanel.ui
