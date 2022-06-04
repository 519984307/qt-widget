#pragma execution_character_set("utf-8")

#include "frmgaugecircle.h"
#include "ui_frmgaugecircle.h"

frmGaugeCircle::frmGaugeCircle(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeCircle)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeCircle::~frmGaugeCircle()
{
    delete ui;
}

void frmGaugeCircle::initForm()
{
    //ui->gaugeCircle->setRange(-200, 200);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeCircle, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
