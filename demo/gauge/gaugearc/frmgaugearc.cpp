#pragma execution_character_set("utf-8")

#include "frmgaugearc.h"
#include "ui_frmgaugearc.h"
#include "gaugearc.h"

frmGaugeArc::frmGaugeArc(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeArc)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeArc::~frmGaugeArc()
{
    delete ui;
}

void frmGaugeArc::initForm()
{
    //设置背景图片
    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/bg1.jpg);}");

    //设置圆弧颜色
    ui->gaugeArc->setArcColor(QColor(0, 255, 255));
    //设置刻度尺颜色
    ui->gaugeArc->setScaleColor(QColor("#00E5EE"));
    //设置刻度尺值颜色
    ui->gaugeArc->setScaleNumColor(QColor(85, 255, 255));
    //绑定滑块拉动值改变触发圆弧表盘值改变
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeArc, SLOT(setValue(int)));

    ui->horizontalSlider->setValue(88);
    ui->ckAnimation->setChecked(false);
    ui->cboxPointerStyle->setCurrentIndex(1);
}

void frmGaugeArc::on_cboxPointerStyle_currentIndexChanged(int index)
{
    //设置指针样式
    ui->gaugeArc->setPointerStyle((GaugeArc::PointerStyle)index);
}

void frmGaugeArc::on_ckAnimation_stateChanged(int arg1)
{
    ui->gaugeArc->setAnimation(arg1 != 0);
}
