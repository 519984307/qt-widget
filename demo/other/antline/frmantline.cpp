﻿#pragma execution_character_set("utf-8")

#include "frmantline.h"
#include "ui_frmantline.h"
#include "qdebug.h"

frmAntLine::frmAntLine(QWidget *parent) : QWidget(parent), ui(new Ui::frmAntLine)
{
    ui->setupUi(this);
    this->initForm();
}

frmAntLine::~frmAntLine()
{
    delete ui;
}

void frmAntLine::initForm()
{
    ui->antLine1->setLineStyle(AntLine::LineStyle_Rect);
    ui->antLine2->setLineStyle(AntLine::LineStyle_RoundedRect);
    ui->antLine3->setLineStyle(AntLine::LineStyle_Ellipse);
    ui->antLine4->setLineStyle(AntLine::LineStyle_Circle);

    ui->antLine1->setLineLen(8);
    ui->antLine2->setLineWidth(6);

    ui->antLine2->setLineColor("#22A3A9");
    ui->antLine3->setLineColor("#A279C5");
    ui->antLine4->setLineColor("#8C2957");
}
