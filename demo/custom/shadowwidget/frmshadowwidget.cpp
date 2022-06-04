#pragma execution_character_set("utf-8")

#include "frmshadowwidget.h"
#include "ui_frmshadowwidget.h"
#include "shadowwidget.h"

frmShadowWidget::frmShadowWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmShadowWidget)
{
    ui->setupUi(this);
    this->initForm();
}

frmShadowWidget::~frmShadowWidget()
{
    delete ui;    
}

void frmShadowWidget::closeEvent(QCloseEvent *)
{
    exit(0);
}

void frmShadowWidget::initForm()
{
    //设置阴影边框颜色
    ui->shadowWidget2->setBorderColor(QColor(71, 164, 233));
    ui->shadowWidget3->setBorderColor(QColor(97, 117, 118));
    ui->shadowWidget4->setBorderColor(QColor(24, 189, 155));

    //设置箭头位置
    ui->shadowWidget2->setTrianglePosition(ShadowWidget::TrianglePosition_Right);
    ui->shadowWidget3->setTrianglePosition(ShadowWidget::TrianglePosition_Bottom);
    ui->shadowWidget4->setTrianglePosition(ShadowWidget::TrianglePosition_Left);
}

void frmShadowWidget::on_btnChange_clicked()
{
    ui->shadowWidget1->setTriangleRatio(0.2);
    ui->shadowWidget1->setTrianglePosition(ShadowWidget::TrianglePosition_Right);
}

void frmShadowWidget::on_btnShow_clicked()
{
    ShadowWidget *shadowWidget = new ShadowWidget;
    //设置箭头的位置
    shadowWidget->setTriangleRatio(0.6);

    //放一个关闭按钮方便关闭弹出的窗体
    QPushButton *btn = new QPushButton(shadowWidget);
    connect(btn, SIGNAL(clicked(bool)), shadowWidget, SLOT(close()));
    btn->setText("关闭");
    btn->move(100, 100);

    shadowWidget->resize(800, 600);
    shadowWidget->show();
}
