QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = gaugedecibel
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugedecibel.cpp
SOURCES     += gaugedecibel.cpp

HEADERS     += frmgaugedecibel.h
HEADERS     += gaugedecibel.h

FORMS       += frmgaugedecibel.ui
