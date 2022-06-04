#pragma execution_character_set("utf-8")

#include "frmgaugecompasspan.h"
#include "ui_frmgaugecompasspan.h"

frmGaugeCompassPan::frmGaugeCompassPan(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeCompassPan)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeCompassPan::~frmGaugeCompassPan()
{
    delete ui;
}

void frmGaugeCompassPan::initForm()
{
    precision = 1;
    ui->gaugecompasspan->setPrecision(precision);
    if (precision == 1) {
        ui->horizontalSlider->setRange(0, 3600);
        ui->horizontalSlider->setValue(1655);
    } else {
        ui->horizontalSlider->setRange(0, 360);
        ui->horizontalSlider->setValue(165);
    }
}

void frmGaugeCompassPan::on_horizontalSlider_valueChanged(int value)
{
    double v = (double)value;
    if (precision == 1) {
        v = v / 10;
    }

    ui->gaugecompasspan->setValue(v);
}
