QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = sliderrange
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmsliderrange.cpp
SOURCES     += sliderrange.cpp

HEADERS     += frmsliderrange.h
HEADERS     += sliderrange.h

FORMS       += frmsliderrange.ui
