QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = imagecalendar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmimagecalendar.cpp
SOURCES     += imagecalendar.cpp
SOURCES     += lunarcalendarinfo.cpp

HEADERS     += frmimagecalendar.h
HEADERS     += imagecalendar.h
HEADERS     += lunarcalendarinfo.h

FORMS       += frmimagecalendar.ui

RESOURCES   += main.qrc
