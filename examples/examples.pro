QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
lessThan(QT_MAJOR_VERSION, 5): QT += script

greaterThan(QT_MAJOR_VERSION, 4) {
!qtHaveModule(xml) {DEFINES += noxmlsvg}
!qtHaveModule(svg) {DEFINES += noxmlsvg}
}

!contains(DEFINES, noxmlsvg) {
QT += xml svg
greaterThan(QT_MAJOR_VERSION, 5): QT += svgwidgets
}

TARGET      = examples
TEMPLATE    = app
MOC_DIR     = temp/moc
RCC_DIR     = temp/rcc
UI_DIR      = temp/ui
OBJECTS_DIR = temp/obj
RC_FILE     = qrc/main.rc

#安卓和web版本不支持指定目录存放编译后生成文件
!android {
!wasm {
DESTDIR     = $$PWD/../bin
}}

#部分环境比如 Qt5.6的debug套件 对预编译头支持不完整 需要注释掉下面这行
PRECOMPILED_HEADER = head.h

CONFIG      += warn_off
HEADERS     += head.h
SOURCES     += main.cpp

#引入资源文件
RESOURCES   += $$PWD/qrc/qmx.qrc
RESOURCES   += $$PWD/qrc/datax.qrc
RESOURCES   += $$PWD/qrc/imagex.qrc
wasm {
RESOURCES   += $$PWD/qrc/fontx.qrc
}

#引入头文件寻找路径
include ($$PWD/examples_include.pri)

DEFINES += examples_full
wasm {
DEFINES -= examples_full
}

#引入示例主窗体
include ($$PWD/frmexamples/frmexamples.pri)
contains(DEFINES, examples_full) {
#引入完整示例
include ($$PWD/examples_full.pri)
} else {
#引入精简示例 一般用来 for web
include ($$PWD/examples_simple.pri)
}
