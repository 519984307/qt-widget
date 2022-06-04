#pragma execution_character_set("utf-8")

#include "frmflightadi.h"
#include "ui_frmflightadi.h"
#include "squarelayout.h"
#include "qdebug.h"

frmFlightADI::frmFlightADI(QWidget *parent) : QWidget(parent), ui(new Ui::frmFlightADI)
{
    ui->setupUi(this);
    this->initForm();
}

frmFlightADI::~frmFlightADI()
{
    delete ui;
}

void frmFlightADI::showEvent(QShowEvent *)
{
    static bool isLoad = false;
    if (!isLoad) {
        isLoad = true;
        ui->sliderRoll->setValue(5);
        ui->sliderPitch->setValue(10);
    }
}

void frmFlightADI::initForm()
{
    //将控件添加到正方形布局中
    SquareLayout *squareLayout = new SquareLayout;
    squareLayout->addWidget(ui->flightADI);

    //新建垂直布局将正方形布局和其他控件加进来
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(squareLayout);
    layout->addWidget(ui->widget);
    this->setLayout(layout);

    ui->sliderRoll->setRange(-180, 180);
    ui->sliderPitch->setRange(-25, 25);
}

void frmFlightADI::on_sliderRoll_valueChanged(int value)
{
    ui->flightADI->setRoll(value);
    ui->labRollValue->setText(QString::number(value));
}

void frmFlightADI::on_sliderPitch_valueChanged(int value)
{
    ui->flightADI->setPitch(value);
    ui->labPitchValue->setText(QString::number(value));
}
