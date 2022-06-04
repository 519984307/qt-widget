#pragma execution_character_set("utf-8")

#include "frmgaugeedit.h"
#include "ui_frmgaugeedit.h"
#include "gaugeedit.h"

frmGaugeEdit::frmGaugeEdit(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeEdit)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeEdit::~frmGaugeEdit()
{
    delete ui;
}

void frmGaugeEdit::initForm()
{
    connect(ui->horizontalSlider1, SIGNAL(valueChanged(int)), ui->gaugeEdit1, SLOT(setValue(int)));
    connect(ui->horizontalSlider2, SIGNAL(valueChanged(int)), ui->gaugeEdit2, SLOT(setValue(int)));
    connect(ui->gaugeEdit1, SIGNAL(valueChanged(int)), ui->horizontalSlider1, SLOT(setValue(int)));
    connect(ui->gaugeEdit2, SIGNAL(valueChanged(int)), ui->horizontalSlider2, SLOT(setValue(int)));

    ui->gaugeEdit1->setUsedColor(QColor(41, 197, 90));
    ui->gaugeEdit2->setUsedColor(QColor(247, 74, 99));

    ui->gaugeEdit1->setRange(-100, 100);
    ui->gaugeEdit2->setRange(0, 100);
    ui->horizontalSlider1->setRange(-100, 100);
    ui->horizontalSlider2->setRange(0, 100);

    ui->horizontalSlider1->setFocus();
    ui->horizontalSlider2->setFocus();
    ui->horizontalSlider1->setValue(65);
    ui->horizontalSlider2->setValue(88);
}
