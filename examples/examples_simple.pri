#引入导航控件
HEADERS += $$path_src/nav/navlistview.h
SOURCES += $$path_src/nav/navlistview.cpp

#引入资源文件
RESOURCES += $$path_designer/qrc/image.qrc
RESOURCES += $$path_designer/qrc/font.qrc
RESOURCES += $$path_designer/qrc/svg.qrc

include ($$PWD/frmsimple/frmgauge.pri)
include ($$PWD/frmsimple/frmprogress.pri)
include ($$PWD/frmsimple/frmpainter.pri)
include ($$PWD/frmsimple/frmcustom.pri)
include ($$PWD/frmsimple/frmnav.pri)
include ($$PWD/frmsimple/frmwave.pri)
include ($$PWD/frmsimple/frmruler.pri)
include ($$PWD/frmsimple/frmslider.pri)
include ($$PWD/frmsimple/frmbar.pri)
include ($$PWD/frmsimple/frmcolor.pri)
include ($$PWD/frmsimple/frmimage.pri)
include ($$PWD/frmsimple/frmother.pri)
include ($$PWD/frmsimple/frmvideo.pri)
include ($$PWD/frmsimple/frmflight.pri)
include ($$PWD/frmsimple/frmxcontrol.pri)
include ($$PWD/frmsimple/frmycontrol.pri)
include ($$PWD/frmsimple/frmwidget.pri)
include ($$PWD/frmsimple/frmcommon.pri)
include ($$PWD/frmsimple/frmtool.pri)
include ($$PWD/frmsimple/frmqtdemo.pri)
