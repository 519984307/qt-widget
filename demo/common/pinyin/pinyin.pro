QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = pinyin
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmpinyin.cpp
SOURCES     += pinyin.cpp

HEADERS     += frmpinyin.h
HEADERS     += pinyin.h

FORMS       += frmpinyin.ui

RESOURCES   += main.qrc
