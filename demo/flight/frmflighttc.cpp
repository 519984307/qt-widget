#pragma execution_character_set("utf-8")

#include "frmflighttc.h"
#include "ui_frmflighttc.h"
#include "squarelayout.h"
#include "qdebug.h"

frmFlightTC::frmFlightTC(QWidget *parent) : QWidget(parent), ui(new Ui::frmFlightTC)
{
    ui->setupUi(this);
    this->initForm();
}

frmFlightTC::~frmFlightTC()
{
    delete ui;
}

void frmFlightTC::showEvent(QShowEvent *)
{
    static bool isLoad = false;
    if (!isLoad) {
        isLoad = true;
        ui->sliderTurnRate->setValue(5);
        ui->sliderSlipSkid->setValue(5);
    }
}

void frmFlightTC::initForm()
{
    //将控件添加到正方形布局中
    SquareLayout *squareLayout = new SquareLayout;
    squareLayout->addWidget(ui->flightTC);

    //新建垂直布局将正方形布局和其他控件加进来
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(squareLayout);
    layout->addWidget(ui->widget);
    this->setLayout(layout);

    ui->sliderTurnRate->setRange(-6, 6);
    ui->sliderSlipSkid->setRange(-15, 15);
}

void frmFlightTC::on_sliderTurnRate_valueChanged(int value)
{
    ui->flightTC->setTurnRate(value);
    ui->labTurnRateValue->setText(QString::number(value));
}

void frmFlightTC::on_sliderSlipSkid_valueChanged(int value)
{
    ui->flightTC->setSlipSkid(value);
    ui->labSlipSkidValue->setText(QString::number(value));
}
