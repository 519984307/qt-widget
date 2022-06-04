QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

greaterThan(QT_MAJOR_VERSION, 4) {
!qtHaveModule(xml) {DEFINES += noxmlsvg}
!qtHaveModule(svg) {DEFINES += noxmlsvg}
}

!contains(DEFINES, noxmlsvg) {
QT += xml svg
greaterThan(QT_MAJOR_VERSION, 5): QT += svgwidgets
}

TARGET      = flight
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off
RESOURCES   += main.qrc

SOURCES     += main.cpp
SOURCES     += squarelayout.cpp
HEADERS     += squarelayout.h

INCLUDEPATH += $$PWD
include($$PWD/frmflight.pri)

INCLUDEPATH += $$PWD/flight
include($$PWD/flight/flight.pri)
