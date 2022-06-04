QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = magicpoolfish
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += magicfish.cpp
SOURCES     += magicpool.cpp
SOURCES     += frmmagicpoolfish.cpp

HEADERS     += magicfish.h
HEADERS     += magicpool.h
HEADERS     += frmmagicpoolfish.h

FORMS       += frmmagicpoolfish.ui
