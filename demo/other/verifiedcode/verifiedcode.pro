QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = verifiedcode
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmverifiedcode.cpp
SOURCES     += verifiedcode.cpp

HEADERS     += frmverifiedcode.h
HEADERS     += verifiedcode.h

FORMS       += frmverifiedcode.ui
