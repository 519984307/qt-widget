#pragma execution_character_set("utf-8")

#include "frmprogresstip.h"
#include "ui_frmprogresstip.h"
#include "qbrush.h"

frmProgressTip::frmProgressTip(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgressTip)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressTip::~frmProgressTip()
{
    delete ui;
}

void frmProgressTip::initForm()
{
    QLinearGradient brush(0, 0, ui->progressTip1->width(), 0);

    brush.setColorAt(0, "#49AFFB");
    brush.setColorAt(1, "#5D51FF");
    ui->progressTip1->setValueBrush(brush);

    brush.setColorAt(0, "#32B9CF");
    brush.setColorAt(1, "#C13256");
    ui->progressTip2->setValueBrush(brush);

    brush.setColorAt(0, "#C13256");
    brush.setColorAt(1, "#32B9CF");
    ui->progressTip3->setValueBrush(brush);

    ui->progressTip3->setRadius(7);
    ui->progressTip4->setRadius(7);
    ui->progressTip3->setValueColor("#FA358A");
    ui->progressTip4->setValueColor("#2EA3EF");
    ui->progressTip3->setTipColor("#FA358A");
    ui->progressTip4->setTipColor("#2EA3EF");

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressTip1, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressTip2, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressTip3, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressTip4, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
