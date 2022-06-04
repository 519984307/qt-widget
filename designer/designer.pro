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

#Qt内部的一些可识别的定义, warn_off 表示关闭警告信息
CONFIG += debug_and_release warn_off
#可定义 staticlib 用来生成静态库
#CONFIG += staticlib

#定义了 quc 则表示生成非插件形式的库文件
DEFINES += quc

#定义了 plugin 则表示生成插件机制的动态库文件,可集成到Qt设计师
#有时候只想生成普通动态库而不是插件,比如嵌入式板子上的Qt很可能没有designer模块
#此时就需要将下面这个定义注释掉才能编译通过
DEFINES += plugin
#有些系统(比如树莓派)上的Qt可能安装的缺少了 designer 模块
#可以尝试用 apt-get install libqt5designer5 apt-get install qttools5-dev 安装
greaterThan(QT_MAJOR_VERSION, 4) {
!qtHaveModule(designer) {
DEFINES -= plugin
}}

#启用了 plugin 则需要引入 designer 模块
contains(DEFINES, plugin) {
greaterThan(QT_MAJOR_VERSION, 4) {
QT += designer
} else {
CONFIG += designer
}}

#手动指定文件名称,debug版本自动在后面加上字母d
CONFIG(debug, debug|release) {
TARGET = qucd
}
CONFIG(release, debug|release) {
TARGET = quc
}

#指定目标生成动态库
TEMPLATE    = lib
#分门别类存放编译文件
MOC_DIR     = temp/moc
RCC_DIR     = temp/rcc
UI_DIR      = temp/ui
OBJECTS_DIR = temp/obj
#指定编译后的文件存放到上级目录下的bin文件夹
DESTDIR     = $$PWD/../bin

#引入资源文件
RESOURCES   += $$PWD/qrc/icon.qrc
RESOURCES   += $$PWD/qrc/font.qrc
RESOURCES   += $$PWD/qrc/image.qrc
!contains(DEFINES, noxmlsvg) {
RESOURCES   += $$PWD/qrc/svg.qrc
}

#引入模块,分门别类存放方便管理
include ($$PWD/src/src.pri)

#将目录加入到编译查找路径,这样在写代码的时候可以省略前面的路径
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/src

contains(DEFINES, plugin) {
include ($$PWD/copy.pri)
include ($$PWD/plugin/plugin.pri)
INCLUDEPATH += $$PWD/plugin
}
