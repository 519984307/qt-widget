QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = tasktableview
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmtasktableview.cpp
SOURCES     += tasktableview.cpp

HEADERS     += frmtasktableview.h
HEADERS     += tasktableview.h

FORMS       += frmtasktableview.ui
