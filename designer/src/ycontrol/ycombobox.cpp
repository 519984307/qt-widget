#pragma execution_character_set("utf-8")

#include "ycombobox.h"
#include "qlistview.h"
#include "yscrollbarv.h"
#include "yscrollbarh.h"
#include "qscrollbar.h"
#include "qevent.h"
#include "qdebug.h"

YComboBox::YComboBox(QWidget *parent) : QComboBox(parent)
{
    isShow = false;

    //设置自定义视图,这样方便设置高度
    listView = new QListView;
    listView->installEventFilter(this);
    this->setView(listView);
    this->installEventFilter(this);

    //自定义widget控制滚动条滚动
    scrollBarV = new YScrollBarV;
    scrollBarV->setScrollBar(listView->verticalScrollBar());

    //先把自带的滚动条隐藏,然后将自定义的widget加进去
    listView->addScrollBarWidget(scrollBarV, Qt::AlignBottom);

    //自定义新的滚动条悬浮于item上
    vscrollBar = new QScrollBar(Qt::Vertical, this->view());
    vscrollBar->setObjectName("vscrollBar");
    connect(listView->verticalScrollBar(), SIGNAL(valueChanged(int)), vscrollBar, SLOT(setValue(int)));
    connect(listView->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(setRange(int, int)));
    connect(vscrollBar, SIGNAL(valueChanged(int)), listView->verticalScrollBar(), SLOT(setValue(int)));

    //设置滚动条位置占用的最小宽度
    listView->verticalScrollBar()->setStyleSheet("width:30px;");
    listView->verticalScrollBar()->setFixedHeight(0);
}

bool YComboBox::eventFilter(QObject *watched, QEvent *event)
{
    //在下拉列表显示的时候移动悬浮滚动条到指定位置
    if (watched == this) {
        if (event->type() == QEvent::Show) {
            if (!isShow) {
                this->initStyle();
                isShow = true;
            }
        }
    } else if (watched == listView) {
        if (event->type() == QEvent::Show) {
            QMetaObject::invokeMethod(this, "setPosition", Qt::QueuedConnection);
        }
    }

    return QComboBox::eventFilter(watched, event);
}

QSize YComboBox::sizeHint() const
{
    return QSize(300, 40);
}

QSize YComboBox::minimumSizeHint() const
{
    return QSize(60, 30);
}

void YComboBox::initStyle()
{
    QStringList list;
    list << QString("YComboBox{border:2px solid #7C7C96;padding-left:5px;padding-right:0px;}");
    list << QString("YComboBox{border-top-right-radius:20px;border-bottom-right-radius:20px;}");
    list << QString("YComboBox::drop-down{width:50px;}");
    list << QString("YComboBox::drop-down{border-image:url(:/image/ycontrol/combox_normal.png);}");
    list << QString("YComboBox::drop-down:on{border-image:url(:/image/ycontrol/combox_select.png);}");
    list << QString("YComboBox::down-arrow{border-width:0px;padding:0px;margin:0px;}");
    list << QString("YComboBox::down-arrow{image:url(:/image/ycontrol/combox_normal_2.png);}");
    list << QString("YComboBox::down-arrow:on{image:url(:/image/ycontrol/combox_select_2.png);}");
    this->setStyleSheet(list.join(""));
}

void YComboBox::setPosition()
{
    bool vbarVisible = listView->verticalScrollBar()->isVisible();
    int scrollWidth = vbarVisible ? 12 : 0;
    int rightWidth = vbarVisible ? 32 : 2;
    int startX = this->width() - scrollWidth - rightWidth;
    vscrollBar->setVisible(vbarVisible);
    vscrollBar->setGeometry(startX, 3, scrollWidth, listView->height() - 6);
    listView->viewport()->setFixedWidth(startX);
}

void YComboBox::setRange(int min, int max)
{
    vscrollBar->setRange(min, max);
}
