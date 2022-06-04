QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = sliderselect
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmsliderselect.cpp
SOURCES     += sliderselect.cpp

HEADERS     += frmsliderselect.h
HEADERS     += sliderselect.h

FORMS       += frmsliderselect.ui
