#pragma execution_character_set("utf-8")

#include "ytablewidget.h"
#include "qheaderview.h"
#include "yscrollbarv.h"
#include "yscrollbarh.h"
#include "qscrollbar.h"
#include "qevent.h"
#include "qdebug.h"

YTableWidget::YTableWidget(QWidget *parent) : QTableWidget(parent)
{
    isShow = false;
    this->installEventFilter(this);

    //自定义widget控制滚动条滚动
    scrollBarV = new YScrollBarV;
    scrollBarV->setScrollBar(this->verticalScrollBar());
    scrollBarH = new YScrollBarH;
    scrollBarH->setScrollBar(this->horizontalScrollBar());

    //先把自带的滚动条隐藏,然后将自定义的widget加进去
    this->addScrollBarWidget(scrollBarV, Qt::AlignBottom);
    this->addScrollBarWidget(scrollBarH, Qt::AlignRight);

    //自定义新的滚动条悬浮于item上
    vscrollBar = new QScrollBar(Qt::Vertical, this);
    vscrollBar->setObjectName("vscrollBar");
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), vscrollBar, SLOT(setValue(int)));
    connect(this->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(setRangeV(int, int)));
    connect(vscrollBar, SIGNAL(valueChanged(int)), this->verticalScrollBar(), SLOT(setValue(int)));

    hscrollBar = new QScrollBar(Qt::Horizontal, this);
    hscrollBar->setObjectName("hscrollBar");
    connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), hscrollBar, SLOT(setValue(int)));
    connect(this->horizontalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(setRangeH(int, int)));
    connect(hscrollBar, SIGNAL(valueChanged(int)), this->horizontalScrollBar(), SLOT(setValue(int)));

    //设置滚动条位置占用的最小宽度
    this->verticalScrollBar()->setStyleSheet("width:30px;");
    this->horizontalScrollBar()->setStyleSheet("height:30px;");
    this->verticalScrollBar()->setFixedHeight(0);
    this->horizontalScrollBar()->setFixedWidth(0);
}

bool YTableWidget::eventFilter(QObject *watched, QEvent *event)
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

    return QTableWidget::eventFilter(watched, event);
}

QSize YTableWidget::sizeHint() const
{
    return QSize(700, 500);
}

QSize YTableWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

void YTableWidget::setPosition()
{
    bool vbarVisible = this->verticalScrollBar()->isVisible();
    int scrollWidth = vbarVisible ? 12 : 0;
    int rightWidth = vbarVisible ? 32 : 2;
    int startX = this->width() - scrollWidth - rightWidth;
    vscrollBar->setVisible(vbarVisible);
    vscrollBar->setGeometry(startX, 3, scrollWidth, this->height() - scrollWidth - rightWidth - 3);
    this->viewport()->setFixedWidth(startX - 3);

    bool hbarVisible = this->horizontalScrollBar()->isVisible();
    int scrollHeight = hbarVisible ? 12 : 0;
    int bottomHeight = hbarVisible ? 32 : 2;
    int startY = this->height() - scrollHeight - bottomHeight;
    hscrollBar->setVisible(hbarVisible);
    hscrollBar->setGeometry(3, startY, this->width() - scrollHeight - bottomHeight, scrollHeight - 3);
    this->viewport()->setFixedHeight(startY - this->horizontalHeader()->height());
}

void YTableWidget::setRangeV(int min, int max)
{
    vscrollBar->setRange(min, max);
}

void YTableWidget::setRangeH(int min, int max)
{
    hscrollBar->setRange(min, max);
}
