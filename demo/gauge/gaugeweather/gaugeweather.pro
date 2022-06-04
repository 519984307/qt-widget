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

TARGET      = gaugeweather
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugeweather.cpp
SOURCES     += gaugeweather.cpp

HEADERS     += frmgaugeweather.h
HEADERS     += gaugeweather.h

FORMS       += frmgaugeweather.ui

RESOURCES   += main.qrc
