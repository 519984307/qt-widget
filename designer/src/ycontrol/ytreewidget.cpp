#pragma execution_character_set("utf-8")

#include "ytreewidget.h"
#include "yscrollbarv.h"
#include "yscrollbarh.h"
#include "qscrollbar.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"

YTreeWidget::YTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    isShow = false;
    this->installEventFilter(this);

    //自定义widget控制滚动条滚动
    scrollBarV = new YScrollBarV;
    scrollBarV->setScrollBar(this->verticalScrollBar());

    //先把自带的滚动条隐藏,然后将自定义的widget加进去
    this->addScrollBarWidget(scrollBarV, Qt::AlignBottom);

    //自定义新的滚动条悬浮于item上
    vscrollBar = new QScrollBar(Qt::Vertical, this);
    vscrollBar->setObjectName("vscrollBar");
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), vscrollBar, SLOT(setValue(int)));
    connect(this->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(setRange(int, int)));
    connect(vscrollBar, SIGNAL(valueChanged(int)), this->verticalScrollBar(), SLOT(setValue(int)));

    //设置滚动条位置占用的最小宽度
    this->verticalScrollBar()->setStyleSheet("width:30px;");
    this->verticalScrollBar()->setFixedHeight(0);
}

bool YTreeWidget::eventFilter(QObject *watched, QEvent *event)
{
    //在下拉列表显示的时候移动悬浮滚动条到指定位置
    if (watched == this) {
        if (event->type() == QEvent::Show) {
            if (!isShow) {
                QMetaObject::invokeMethod(this, "setPosition", Qt::QueuedConnection);
                isShow = true;
            }
        } else if (event->type() == QEvent::Resize) {
            QMetaObject::invokeMethod(this, "setPosition", Qt::QueuedConnection);
        }
    }

    return QTreeWidget::eventFilter(watched, event);
}

QSize YTreeWidget::sizeHint() const
{
    return QSize(300, 500);
}

QSize YTreeWidget::minimumSizeHint() const
{
    return QSize(30, 50);
}

void YTreeWidget::setPosition()
{
    bool vbarVisible = this->verticalScrollBar()->isVisible();
    int scrollWidth = vbarVisible ? 12 : 0;
    int rightWidth = vbarVisible ? 32 : 2;
    int startX = this->width() - scrollWidth - rightWidth;
    vscrollBar->setVisible(vbarVisible);
    vscrollBar->setGeometry(startX, 3, scrollWidth, this->height() - 6);
    this->viewport()->setFixedWidth(startX - 3);
}

void YTreeWidget::setRange(int min, int max)
{
    vscrollBar->setRange(min, max);
}
