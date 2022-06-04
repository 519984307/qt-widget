#pragma execution_character_set("utf-8")

#include "frmgaugecolor.h"
#include "ui_frmgaugecolor.h"
#include "gaugecolor.h"

frmGaugeColor::frmGaugeColor(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeColor)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeColor::~frmGaugeColor()
{
    delete ui;
}

void frmGaugeColor::initForm()
{
    //设置范围值
    //ui->gaugeColor->setRange(-100, 100);
    //关联滑块值改变信号自动设置仪表盘的值
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeColor, SLOT(setValue(int)));
    //设置滑块初始值
    ui->horizontalSlider->setValue(88);
    //默认选中动画效果
    ui->ckAnimation->setChecked(true);
    //指针类型
    ui->cboxPointerStyle->setCurrentIndex(1);
}

void frmGaugeColor::on_cboxPointerStyle_currentIndexChanged(int index)
{
    //指针类型下拉框值切换后自动设置仪表盘对应的指针类型
    ui->gaugeColor->setPointerStyle((GaugeColor::PointerStyle)index);
}

void frmGaugeColor::on_ckAnimation_stateChanged(int arg1)
{
    //启用和禁用动画效果
    ui->gaugeColor->setAnimation(arg1 != 0);
}
