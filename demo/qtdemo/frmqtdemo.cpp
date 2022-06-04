﻿#pragma execution_character_set("utf-8")

#include "frmqtdemo.h"
#include "ui_frmqtdemo.h"

#include "xform.h"
#include "composition.h"
#include "gradients.h"
#include "pathdeform.h"
#include "pathstroke.h"

frmQtDemo::frmQtDemo(QWidget *parent) : QWidget(parent), ui(new Ui::frmQtDemo)
{
    ui->setupUi(this);
    this->initForm();
}

frmQtDemo::~frmQtDemo()
{
    delete ui;
}

void frmQtDemo::initForm()
{
    ui->stackedWidget->addWidget(new XFormWidget);
    ui->stackedWidget->addWidget(new CompositionWidget);
    ui->stackedWidget->addWidget(new GradientWidget);
    ui->stackedWidget->addWidget(new PathDeformWidget);
    ui->stackedWidget->addWidget(new PathStrokeWidget);
}

void frmQtDemo::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
