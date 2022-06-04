#pragma execution_character_set("utf-8")

#include "frmflightpfd.h"
#include "ui_frmflightpfd.h"
#include "squarelayout.h"
#include "qdebug.h"

frmFlightPFD::frmFlightPFD(QWidget *parent) : QWidget(parent), ui(new Ui::frmFlightPFD)
{
    ui->setupUi(this);
    this->initForm();
}

frmFlightPFD::~frmFlightPFD()
{
    delete ui;
}

void frmFlightPFD::showEvent(QShowEvent *)
{
    static bool isLoad = false;
    if (!isLoad) {
        isLoad = true;
        ui->sliderRoll->setValue(120);
        ui->sliderPitch->setValue(15);
        ui->sliderAltitude->setValue(5000);
        ui->sliderHeading->setValue(120);
        ui->sliderAirspeed->setValue(2000);
        ui->sliderDistance->setValue(230);
    }
}

void frmFlightPFD::initForm()
{
    //将控件添加到正方形布局中
    SquareLayout *squareLayout = new SquareLayout;
    squareLayout->addWidget(ui->flightPFD);

    //新建垂直布局将正方形布局和其他控件加进来
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(squareLayout);
    layout->addWidget(ui->widget);
    this->setLayout(layout);

    ui->sliderRoll->setRange(-180, 180);
    ui->sliderPitch->setRange(-25, 25);
    ui->sliderAltitude->setRange(0, 10000);
    ui->sliderHeading->setRange(0, 360);
    ui->sliderAirspeed->setRange(0, 9999);
    ui->sliderDistance->setRange(0, 360);
}

void frmFlightPFD::on_sliderRoll_valueChanged(int value)
{
    ui->flightPFD->setRoll(value);
    ui->labRollValue->setText(QString::number(value));
}

void frmFlightPFD::on_sliderPitch_valueChanged(int value)
{
    ui->flightPFD->setPitch(value);
    ui->labPitchValue->setText(QString::number(value));
}

void frmFlightPFD::on_sliderAltitude_valueChanged(int value)
{
    ui->flightPFD->setAltitude(value);
    ui->labAltitudeValue->setText(QString::number(value));
}

void frmFlightPFD::on_sliderHeading_valueChanged(int value)
{
    ui->flightPFD->setHeading(value);
    ui->labHeadingValue->setText(QString::number(value));
}

void frmFlightPFD::on_sliderAirspeed_valueChanged(int value)
{
    ui->flightPFD->setAirspeed(value);
    ui->labAirspeedValue->setText(QString::number(value));
}

void frmFlightPFD::on_sliderDistance_valueChanged(int value)
{
    ui->flightPFD->setDistance(value, true);
    ui->labDistanceValue->setText(QString::number(value));
}
