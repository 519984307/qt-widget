#pragma execution_character_set("utf-8")

#include "frmflightvsi.h"
#include "ui_frmflightvsi.h"
#include "squarelayout.h"
#include "qdebug.h"

frmFlightVSI::frmFlightVSI(QWidget *parent) : QWidget(parent), ui(new Ui::frmFlightVSI)
{
    ui->setupUi(this);
    this->initForm();
}

frmFlightVSI::~frmFlightVSI()
{
    delete ui;
}

void frmFlightVSI::showEvent(QShowEvent *)
{
    static bool isLoad = false;
    if (!isLoad) {
        isLoad = true;
        ui->sliderClimbRate->setValue(1000);
    }
}

void frmFlightVSI::initForm()
{
    //将控件添加到正方形布局中
    SquareLayout *squareLayout = new SquareLayout;
    squareLayout->addWidget(ui->flightVSI);

    //新建垂直布局将正方形布局和其他控件加进来
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(squareLayout);
    layout->addWidget(ui->widget);
    this->setLayout(layout);

    ui->sliderClimbRate->setRange(-2000, 2000);
}

void frmFlightVSI::on_sliderClimbRate_valueChanged(int value)
{
    ui->flightVSI->setClimbRate(value);
    ui->labClimbRateValue->setText(QString::number(value));
}
