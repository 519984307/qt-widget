#如果定义了alone则表示以源码形式集成编译到examples中,否则以控件以动态库形式集成
#一般编译android版本需要改成alone
DEFINES += alone1
android {
DEFINES += alone
}

contains(DEFINES, alone) {
include ($$path_src/src.pri)
INCLUDEPATH += $$path_designer/src
RESOURCES   += $$path_designer/qrc/image.qrc
RESOURCES   += $$path_designer/qrc/font.qrc
RESOURCES   += $$path_designer/qrc/svg.qrc
} else {
CONFIG(debug, debug|release) {
LIBS += -L$$PWD/../bin/ -lqucd
} else {
LIBS += -L$$PWD/../bin/ -lquc
}}

include ($$PWD/frmall/frmall.pri)
include ($$PWD/frmfull/frmgauge.pri)
include ($$PWD/frmfull/frmprogress.pri)
include ($$PWD/frmfull/frmpainter.pri)
include ($$PWD/frmfull/frmcustom.pri)
include ($$PWD/frmfull/frmnav.pri)
include ($$PWD/frmfull/frmwave.pri)
include ($$PWD/frmfull/frmruler.pri)
include ($$PWD/frmfull/frmslider.pri)
include ($$PWD/frmfull/frmbar.pri)
include ($$PWD/frmfull/frmcolor.pri)
include ($$PWD/frmfull/frmimage.pri)
include ($$PWD/frmfull/frmother.pri)
include ($$PWD/frmfull/frmvideo.pri)
include ($$PWD/frmfull/frmflight.pri)
include ($$PWD/frmfull/frmxcontrol.pri)
include ($$PWD/frmfull/frmycontrol.pri)
include ($$PWD/frmfull/frmwidget.pri)
include ($$PWD/frmfull/frmcommon.pri)
include ($$PWD/frmfull/frmtool.pri)
include ($$PWD/frmfull/frmqtdemo.pri)
