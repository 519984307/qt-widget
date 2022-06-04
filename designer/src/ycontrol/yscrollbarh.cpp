#pragma execution_character_set("utf-8")

#include "yscrollbarh.h"
#include "qscrollbar.h"
#include "qpushbutton.h"
#include "qlayout.h"
#include "qdebug.h"

YScrollBarH::YScrollBarH(QWidget *parent) : QWidget(parent)
{
    scrollBar = 0;
    stepSingle = 1;
    stepDouble = 2;

    //实例化6个按钮用于单击滚动条滚动
    QPushButton *btnLeft1 = new QPushButton;
    btnLeft1->setObjectName("btnLeft1");
    QPushButton *btnLeft2 = new QPushButton;
    btnLeft2->setObjectName("btnLeft2");
    QPushButton *btnLeft3 = new QPushButton;
    btnLeft3->setObjectName("btnLeft3");

    QPushButton *btnRight1 = new QPushButton;
    btnRight1->setObjectName("btnRight1");
    QPushButton *btnRight2 = new QPushButton;
    btnRight2->setObjectName("btnRight2");
    QPushButton *btnRight3 = new QPushButton;
    btnRight3->setObjectName("btnRight3");

    //设置上下布局
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(btnLeft1);
    layout->addWidget(btnLeft2);
    layout->addWidget(btnLeft3);
    layout->addStretch();
    layout->addWidget(btnRight1);
    layout->addWidget(btnRight2);
    layout->addWidget(btnRight3);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
    this->initStyle();

    //关联单击事件
    QList<QPushButton *> btns = this->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
    }
}

int YScrollBarH::getStepSingle() const
{
    return this->stepSingle;
}

int YScrollBarH::getStepDouble() const
{
    return this->stepDouble;
}

void YScrollBarH::initStyle()
{
    //设置按钮样式
    QStringList list;
    list << QString("QPushButton{min-width:50px;min-height:30px;}");
    list << QString("QPushButton{border-image:url(:/image/ycontrol/HScrollbarButton_normal.png);}");
    list << QString("QPushButton:pressed{border-image:url(:/image/ycontrol/HScrollbarButton_select.png);}");
    list << QString("#btnLeft1{image:url(:/image/ycontrol/HScrollbarButton_normal_minus---.png)}");
    list << QString("#btnLeft1:pressed{image:url(:/image/ycontrol/HScrollbarButton_select_minus---.png)}");
    list << QString("#btnLeft2{image:url(:/image/ycontrol/HScrollbarButton_normal_minus--.png)}");
    list << QString("#btnLeft2:pressed{image:url(:/image/ycontrol/HScrollbarButton_select_minus--.png)}");
    list << QString("#btnLeft3{image:url(:/image/ycontrol/HScrollbarButton_normal_minus-.png)}");
    list << QString("#btnLeft3:pressed{image:url(:/image/ycontrol/HScrollbarButton_select_minus-.png)}");
    list << QString("#btnRight1{image:url(:/image/ycontrol/HScrollbarButton_normal_plus+.png)}");
    list << QString("#btnRight1:pressed{image:url(:/image/ycontrol/HScrollbarButton_select_plus+.png)}");
    list << QString("#btnRight2{image:url(:/image/ycontrol/HScrollbarButton_normal_plus++.png)}");
    list << QString("#btnRight2:pressed{image:url(:/image/ycontrol/HScrollbarButton_select_plus++.png)}");
    list << QString("#btnRight3{image:url(:/image/ycontrol/HScrollbarButton_normal_plus+++.png)}");
    list << QString("#btnRight3:pressed{image:url(:/image/ycontrol/HScrollbarButton_select_plus+++.png)}");
    this->setStyleSheet(list.join(""));
}

void YScrollBarH::buttonClicked()
{
    if (scrollBar == 0) {
        return;
    }

    QPushButton *btn = (QPushButton *)sender();
    QString objName = btn->objectName();

    //判断不同的按钮滚动不同的距离
    int value = scrollBar->value();
    if (objName == "btnLeft1") {
        scrollBar->setValue(0);
    } else if (objName == "btnLeft2") {
        scrollBar->setValue(value - stepDouble);
    } else if (objName == "btnLeft3") {
        scrollBar->setValue(value - stepSingle);
    } else if (objName == "btnRight1") {
        scrollBar->setValue(value + stepSingle);
    } else if (objName == "btnRight2") {
        scrollBar->setValue(value + stepDouble);
    } else if (objName == "btnRight3") {
        scrollBar->setValue(scrollBar->maximum());
    }
}

void YScrollBarH::setScrollBar(QScrollBar *scrollBar)
{
    this->scrollBar = scrollBar;
}

void YScrollBarH::setStepSingle(int stepSingle)
{
    this->stepSingle = stepSingle;
}

void YScrollBarH::setStepDouble(int stepDouble)
{
    this->stepDouble = stepDouble;
}
