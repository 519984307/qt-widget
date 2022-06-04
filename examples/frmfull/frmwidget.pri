FORMS += \
    $$PWD/../../demo/widget/bottomwidget/frmbottomwidget.ui \
    $$PWD/../../demo/widget/colorwidget/frmcolorwidget.ui \
    $$PWD/../../demo/widget/framelesswidget/frmframelesswidget.ui \
    $$PWD/../../demo/widget/gifwidget/frmgifwidget.ui \
    $$PWD/../../demo/widget/maskwidget/frmmaskwidget.ui \
    $$PWD/../../demo/widget/movewidget/frmmovewidget.ui \
    $$PWD/../../demo/widget/screenwidget/frmscreenwidget.ui

HEADERS += \
    $$PWD/../../demo/widget/bottomwidget/frmbottomwidget.h \
    $$PWD/../../demo/widget/colorwidget/frmcolorwidget.h \
    $$PWD/../../demo/widget/framelesswidget/frmframelesswidget.h \
    $$PWD/../../demo/widget/gifwidget/frmgifwidget.h \
    $$PWD/../../demo/widget/maskwidget/frmmaskwidget.h \
    $$PWD/../../demo/widget/movewidget/frmmovewidget.h \
    $$PWD/../../demo/widget/screenwidget/frmscreenwidget.h

SOURCES += \
    $$PWD/../../demo/widget/bottomwidget/frmbottomwidget.cpp \
    $$PWD/../../demo/widget/colorwidget/frmcolorwidget.cpp \
    $$PWD/../../demo/widget/framelesswidget/frmframelesswidget.cpp \
    $$PWD/../../demo/widget/gifwidget/frmgifwidget.cpp \
    $$PWD/../../demo/widget/maskwidget/frmmaskwidget.cpp \
    $$PWD/../../demo/widget/movewidget/frmmovewidget.cpp \
    $$PWD/../../demo/widget/screenwidget/frmscreenwidget.cpp

!msvc {
FORMS += \
    $$PWD/../../demo/widget/framelesswidget/framelessform/dialog.ui \
    $$PWD/../../demo/widget/framelesswidget/framelessform/mainwindow.ui \
    $$PWD/../../demo/widget/framelesswidget/framelessform/widget.ui

HEADERS += \
    $$PWD/../../demo/widget/framelesswidget/framelessform/dialog.h \
    $$PWD/../../demo/widget/framelesswidget/framelessform/mainwindow.h \
    $$PWD/../../demo/widget/framelesswidget/framelessform/widget.h

SOURCES += \
    $$PWD/../../demo/widget/framelesswidget/framelessform/dialog.cpp \
    $$PWD/../../demo/widget/framelesswidget/framelessform/mainwindow.cpp \
    $$PWD/../../demo/widget/framelesswidget/framelessform/widget.cpp
}
