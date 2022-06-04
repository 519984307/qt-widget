#pragma execution_character_set("utf-8")

#include "yscrollbarv.h"
#include "qscrollbar.h"
#include "qpushbutton.h"
#include "qlayout.h"
#include "qdebug.h"

YScrollBarV::YScrollBarV(QWidget *parent) : QWidget(parent)
{
    scrollBar = 0;
    stepSingle = 1;
    stepDouble = 2;

    //实例化6个按钮用于单击滚动条滚动
    QPushButton *btnTop1 = new QPushButton;
    btnTop1->setObjectName("btnTop1");
    QPushButton *btnTop2 = new QPushButton;
    btnTop2->setObjectName("btnTop2");
    QPushButton *btnTop3 = new QPushButton;
    btnTop3->setObjectName("btnTop3");

    QPushButton *btnBottom1 = new QPushButton;
    btnBottom1->setObjectName("btnBottom1");
    QPushButton *btnBottom2 = new QPushButton;
    btnBottom2->setObjectName("btnBottom2");
    QPushButton *btnBottom3 = new QPushButton;
    btnBottom3->setObjectName("btnBottom3");

    //设置上下布局
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(btnTop1);
    layout->addWidget(btnTop2);
    layout->addWidget(btnTop3);
    layout->addStretch();
    layout->addWidget(btnBottom1);
    layout->addWidget(btnBottom2);
    layout->addWidget(btnBottom3);
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

int YScrollBarV::getStepSingle() const
{
    return this->stepSingle;
}

int YScrollBarV::getStepDouble() const
{
    return this->stepDouble;
}

void YScrollBarV::initStyle()
{
    //设置按钮样式
    QStringList list;
    list << QString("QPushButton{min-width:30px;min-height:50px;}");
    list << QString("QPushButton{border-image:url(:/image/ycontrol/VScrollbarButton_normal.png);}");
    list << QString("QPushButton:pressed{border-image:url(:/image/ycontrol/VScrollbarButton_select.png);}");
    list << QString("#btnTop1{image:url(:/image/ycontrol/VScrollbarButton_normal_plus+++.png)}");
    list << QString("#btnTop1:pressed{image:url(:/image/ycontrol/VScrollbarButton_select_plus+++.png)}");
    list << QString("#btnTop2{image:url(:/image/ycontrol/VScrollbarButton_normal_plus++.png)}");
    list << QString("#btnTop2:pressed{image:url(:/image/ycontrol/VScrollbarButton_select_plus++.png)}");
    list << QString("#btnTop3{image:url(:/image/ycontrol/VScrollbarButton_normal_plus+.png)}");
    list << QString("#btnTop3:pressed{image:url(:/image/ycontrol/VScrollbarButton_select_plus+.png)}");
    list << QString("#btnBottom1{image:url(:/image/ycontrol/VScrollbarButton_normal_minus-.png)}");
    list << QString("#btnBottom1:pressed{image:url(:/image/ycontrol/VScrollbarButton_select_minus-.png)}");
    list << QString("#btnBottom2{image:url(:/image/ycontrol/VScrollbarButton_normal_minus--.png)}");
    list << QString("#btnBottom2:pressed{image:url(:/image/ycontrol/VScrollbarButton_select_minus--.png)}");
    list << QString("#btnBottom3{image:url(:/image/ycontrol/VScrollbarButton_normal_minus---.png)}");
    list << QString("#btnBottom3:pressed{image:url(:/image/ycontrol/VScrollbarButton_select_minus---.png)}");
    this->setStyleSheet(list.join(""));
}

void YScrollBarV::buttonClicked()
{
    if (scrollBar == 0) {
        return;
    }

    QPushButton *btn = (QPushButton *)sender();
    QString objName = btn->objectName();

    //判断不同的按钮滚动不同的距离
    int value = scrollBar->value();
    if (objName == "btnTop1") {
        scrollBar->setValue(0);
    } else if (objName == "btnTop2") {
        scrollBar->setValue(value - stepDouble);
    } else if (objName == "btnTop3") {
        scrollBar->setValue(value - stepSingle);
    } else if (objName == "btnBottom1") {
        scrollBar->setValue(value + stepSingle);
    } else if (objName == "btnBottom2") {
        scrollBar->setValue(value + stepDouble);
    } else if (objName == "btnBottom3") {
        scrollBar->setValue(scrollBar->maximum());
    }
}

void YScrollBarV::setScrollBar(QScrollBar *scrollBar)
{
    this->scrollBar = scrollBar;
}

void YScrollBarV::setStepSingle(int stepSingle)
{
    this->stepSingle = stepSingle;
}

void YScrollBarV::setStepDouble(int stepDouble)
{
    this->stepDouble = stepDouble;
}
