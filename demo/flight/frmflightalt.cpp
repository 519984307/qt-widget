#pragma execution_character_set("utf-8")

#include "frmflightalt.h"
#include "ui_frmflightalt.h"
#include "squarelayout.h"
#include "qdebug.h"

frmFlightALT::frmFlightALT(QWidget *parent) : QWidget(parent), ui(new Ui::frmFlightALT)
{
    ui->setupUi(this);
    this->initForm();
}

frmFlightALT::~frmFlightALT()
{
    delete ui;
}

void frmFlightALT::showEvent(QShowEvent *)
{
    static bool isLoad = false;
    if (!isLoad) {
        isLoad = true;
        ui->sliderAltitude->setValue(650);
        ui->sliderPressure->setValue(300);
    }
}

void frmFlightALT::initForm()
{
    //将控件添加到正方形布局中
    SquareLayout *squareLayout = new SquareLayout;
    squareLayout->addWidget(ui->flightALT);

    //新建垂直布局将正方形布局和其他控件加进来
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(squareLayout);
    layout->addWidget(ui->widget);
    this->setLayout(layout);

    ui->sliderAltitude->setRange(0, 10000);
    ui->sliderPressure->setRange(280, 315);
}

void frmFlightALT::on_sliderAltitude_valueChanged(int value)
{
    ui->flightALT->setAltitude(value);
    ui->labAltitudeValue->setText(QString::number(value));
}

void frmFlightALT::on_sliderPressure_valueChanged(int value)
{
    ui->flightALT->setPressure((float)value / 10);
    ui->labPressureValue->setText(QString::number((float)value / 10));
}
