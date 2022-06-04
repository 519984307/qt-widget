#pragma execution_character_set("utf-8")

#include "frmgaugecompass2.h"
#include "ui_frmgaugecompass2.h"

frmGaugeCompass2::frmGaugeCompass2(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeCompass2)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeCompass2::~frmGaugeCompass2()
{
    delete ui;
}

void frmGaugeCompass2::initForm()
{
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeCompass2, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(180);
}
