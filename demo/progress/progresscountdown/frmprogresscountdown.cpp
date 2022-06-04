#pragma execution_character_set("utf-8")

#include "frmprogresscountdown.h"
#include "ui_frmprogresscountdown.h"

frmProgressCountDown::frmProgressCountDown(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgressCountDown)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressCountDown::~frmProgressCountDown()
{
    delete ui;
}

void frmProgressCountDown::initForm()
{
    ui->progressCountDown2->setLineWidth(10);
    ui->progressCountDown2->setLineColor(QColor(71, 164, 233));

    ui->progressCountDown2->setBorderWidth(10);
    ui->progressCountDown2->setBorderColor(QColor(94, 199, 217));

    ui->progressCountDown2->setBgColor(QColor(50, 185, 207));
}
