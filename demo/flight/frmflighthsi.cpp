#pragma execution_character_set("utf-8")

#include "frmflighthsi.h"
#include "ui_frmflighthsi.h"
#include "squarelayout.h"
#include "qdebug.h"

frmFlightHSI::frmFlightHSI(QWidget *parent) : QWidget(parent), ui(new Ui::frmFlightHSI)
{
    ui->setupUi(this);
    this->initForm();
}

frmFlightHSI::~frmFlightHSI()
{
    delete ui;
}

void frmFlightHSI::showEvent(QShowEvent *)
{
    static bool isLoad = false;
    if (!isLoad) {
        isLoad = true;
        ui->sliderHeading->setValue(180);
    }
}

void frmFlightHSI::initForm()
{
    //将控件添加到正方形布局中
    SquareLayout *squareLayout = new SquareLayout;
    squareLayout->addWidget(ui->flightHSI);

    //新建垂直布局将正方形布局和其他控件加进来
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(squareLayout);
    layout->addWidget(ui->widget);
    this->setLayout(layout);

    ui->sliderHeading->setRange(0, 360);
}

void frmFlightHSI::on_sliderHeading_valueChanged(int value)
{
    ui->flightHSI->setHeading(value);
    ui->labHeadingValue->setText(QString::number(value));
}
