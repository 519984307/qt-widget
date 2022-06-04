HEADERS += $$PWD/qucplugin.h
SOURCES += $$PWD/qucplugin.cpp

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/gauge
INCLUDEPATH += $$PWD/progress
INCLUDEPATH += $$PWD/painter
INCLUDEPATH += $$PWD/custom
INCLUDEPATH += $$PWD/nav
INCLUDEPATH += $$PWD/wave
INCLUDEPATH += $$PWD/ruler
INCLUDEPATH += $$PWD/slider
INCLUDEPATH += $$PWD/bar
INCLUDEPATH += $$PWD/color
INCLUDEPATH += $$PWD/image
INCLUDEPATH += $$PWD/other
INCLUDEPATH += $$PWD/video
INCLUDEPATH += $$PWD/flight
INCLUDEPATH += $$PWD/xcontrol
INCLUDEPATH += $$PWD/ycontrol

include ($$PWD/gauge/gauge.pri)
include ($$PWD/progress/progress.pri)
include ($$PWD/painter/painter.pri)
include ($$PWD/custom/custom.pri)
include ($$PWD/nav/nav.pri)
include ($$PWD/wave/wave.pri)
include ($$PWD/ruler/ruler.pri)
include ($$PWD/slider/slider.pri)
include ($$PWD/bar/bar.pri)
include ($$PWD/color/color.pri)
include ($$PWD/image/image.pri)
include ($$PWD/other/other.pri)
include ($$PWD/video/video.pri)
include ($$PWD/flight/flight.pri)
include ($$PWD/xcontrol/xcontrol.pri)
include ($$PWD/ycontrol/ycontrol.pri)
