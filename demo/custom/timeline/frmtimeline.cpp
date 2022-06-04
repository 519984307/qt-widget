#pragma execution_character_set("utf-8")
#include "frmtimeline.h"
#include "ui_frmtimeline.h"
#include "qdebug.h"

frmTimeLine::frmTimeLine(QWidget *parent) : QWidget(parent), ui(new Ui::frmTimeLine)
{
    ui->setupUi(this);
    this->initForm();
}

frmTimeLine::~frmTimeLine()
{
    delete ui;
}

void frmTimeLine::initForm()
{
    ui->timeLine2->setScaled(30);
    ui->timeLine3->setScaled(55);
    ui->timeLine1->setLineColor(QColor(255, 107, 107, 200));
    ui->timeLine2->setLineColor(QColor(34, 163, 169, 200));
    ui->timeLine3->setLineColor(QColor(162, 121, 197, 200));
}
