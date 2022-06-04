#pragma execution_character_set("utf-8")

#include "frmsliderrange.h"
#include "ui_frmsliderrange.h"

frmSliderRange::frmSliderRange(QWidget *parent) : QWidget(parent), ui(new Ui::frmSliderRange)
{
    ui->setupUi(this);
    this->initForm();
}

frmSliderRange::~frmSliderRange()
{
    delete ui;
}

void frmSliderRange::initForm()
{
    ui->sliderRange2->setCurrentRange(10, 80);
    ui->sliderRange3->setCurrentRange(30, 70);
    ui->sliderRange4->setCurrentRange(50, 90);

    ui->sliderRange3->setShowText(true);
    ui->sliderRange4->setShowText(true);
    ui->sliderRange3->setSliderStyle(SliderRange::SliderStyle_Circle);
    ui->sliderRange4->setSliderStyle(SliderRange::SliderStyle_Circle);

    ui->sliderRange2->setUsedColor(QColor(255, 107, 107));
    ui->sliderRange4->setUsedColor(QColor(255, 107, 107));
}
