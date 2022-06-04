QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = rulerprogress
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp \
    rulerprogress.cpp \
    frmrulerprogress.cpp
SOURCES     +=
SOURCES     +=

HEADERS     += \
    rulerprogress.h \
    frmrulerprogress.h
HEADERS     +=

FORMS       += \
    frmrulerprogress.ui
