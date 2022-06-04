#pragma execution_character_set("utf-8")

#include "frmflightasi.h"
#include "ui_frmflightasi.h"
#include "squarelayout.h"
#include "qdebug.h"

frmFlightASI::frmFlightASI(QWidget *parent) : QWidget(parent), ui(new Ui::frmFlightASI)
{
    ui->setupUi(this);
    this->initForm();
}

frmFlightASI::~frmFlightASI()
{
    delete ui;
}

void frmFlightASI::showEvent(QShowEvent *)
{
    static bool isLoad = false;
    if (!isLoad) {
        isLoad = true;
        ui->sliderAirspeed->setValue(88);
    }
}

void frmFlightASI::initForm()
{
    //将控件添加到正方形布局中
    SquareLayout *squareLayout = new SquareLayout;
    squareLayout->addWidget(ui->flightASI);

    //新建垂直布局将正方形布局和其他控件加进来
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(squareLayout);
    layout->addWidget(ui->widget);
    this->setLayout(layout);

    ui->sliderAirspeed->setRange(0, 235);
}

void frmFlightASI::on_sliderAirspeed_valueChanged(int value)
{
    ui->flightASI->setAirspeed(value);
    ui->labAirspeedValue->setText(QString::number(value));
}
