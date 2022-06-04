QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = ycontrol
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off
RESOURCES   += main.qrc

SOURCES     += main.cpp

INCLUDEPATH += $$PWD
include($$PWD/frmycontrol.pri)

INCLUDEPATH += $$PWD/ycontrol
include ($$PWD/ycontrol/ycontrol.pri)
