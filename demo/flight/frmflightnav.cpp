#pragma execution_character_set("utf-8")

#include "frmflightnav.h"
#include "ui_frmflightnav.h"
#include "squarelayout.h"
#include "qdebug.h"

frmFlightNAV::frmFlightNAV(QWidget *parent) : QWidget(parent), ui(new Ui::frmFlightNAV)
{
    ui->setupUi(this);
    this->initForm();
}

frmFlightNAV::~frmFlightNAV()
{
    delete ui;
}

void frmFlightNAV::showEvent(QShowEvent *)
{
    static bool isLoad = false;
    if (!isLoad) {
        isLoad = true;
        ui->sliderHeading->setValue(200);
        ui->sliderHeadingBug->setValue(150);
        ui->sliderCourse->setValue(100);
        ui->sliderBearing->setValue(130);
        ui->sliderDeviation->setValue(88);
        ui->sliderDistance->setValue(300);
    }
}

void frmFlightNAV::initForm()
{
    //将控件添加到正方形布局中
    SquareLayout *squareLayout = new SquareLayout;
    squareLayout->addWidget(ui->flightNAV);

    //新建垂直布局将正方形布局和其他控件加进来
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(squareLayout);
    layout->addWidget(ui->widget);
    this->setLayout(layout);

    ui->sliderHeading->setRange(0, 360);
    ui->sliderHeadingBug->setRange(0, 360);
    ui->sliderCourse->setRange(0, 360);
    ui->sliderBearing->setRange(0, 360);
    ui->sliderDeviation->setRange(0, 100);
    ui->sliderDistance->setRange(0, 360);
}

void frmFlightNAV::on_sliderHeading_valueChanged(int value)
{
    ui->flightNAV->setHeading(value);
    ui->labHeadingValue->setText(QString::number(value));
}

void frmFlightNAV::on_sliderHeadingBug_valueChanged(int value)
{
    ui->flightNAV->setHeadingBug(value);
    ui->labHeadingBugValue->setText(QString::number(value));
}

void frmFlightNAV::on_sliderCourse_valueChanged(int value)
{
    ui->flightNAV->setCourse(value);
    ui->labCourseValue->setText(QString::number(value));
}

void frmFlightNAV::on_sliderBearing_valueChanged(int value)
{
    ui->flightNAV->setBearing(value);
    ui->labBearingValue->setText(QString::number(value));
}

void frmFlightNAV::on_sliderDeviation_valueChanged(int value)
{
    ui->flightNAV->setDeviation((float)value / 100);
    ui->labDeviationValue->setText(QString::number((float)value / 100));
}

void frmFlightNAV::on_sliderDistance_valueChanged(int value)
{
    ui->flightNAV->setDistance(value);
    ui->labDistanceValue->setText(QString::number(value));
}
