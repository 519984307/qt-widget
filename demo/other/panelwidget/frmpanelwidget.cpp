#pragma execution_character_set("utf-8")

#include "frmpanelwidget.h"
#include "ui_frmpanelwidget.h"
#include "qpushbutton.h"
#include "frmpanelwidgetx.h"

frmPanelWidget::frmPanelWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmPanelWidget)
{
    ui->setupUi(this);
    this->initForm();
    this->test();
}

frmPanelWidget::~frmPanelWidget()
{
    delete ui;
}

void frmPanelWidget::initForm()
{
    for (int i = 1; i <= 100; i++) {
        QPushButton *btn = new QPushButton;
        btn->setText(QString::number(i));
        btn->setFixedHeight(100);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        widgets1.append(btn);
    }

    ui->widget1->setContentsMargins(3, 3, 3, 3);
    ui->widget1->setColumnCount(10);
    ui->widget1->setWidgets(widgets1);

    for (int i = 1; i <= 50; i++) {
        frmPanelWidgetX *frm = new frmPanelWidgetX;
        frm->setFixedHeight(105);
        frm->setMinimumWidth(200);
        frm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        //设置唯一标识,可以自定义,这里填 0001 0002 之类的
        frm->setFlag(QString("%1").arg(i, 4, 10, QChar('0')));
        widgets2.append(frm);
    }

    ui->widget2->setMargin(3, 3, 3, 3);
    ui->widget2->setColumnCount(6);
    ui->widget2->setWidgets(widgets2);
}

void frmPanelWidget::test()
{
    //测试改变面板中一个子窗体的值
    foreach (QWidget *widget, widgets2) {
        //转换成原始的窗体类
        frmPanelWidgetX *frm = (frmPanelWidgetX *)widget;
        //改变标识符=0002的这个窗体中的数据
        if (frm->getFlag() == "0002") {
            frm->setValue(99);
        }
    }
}
