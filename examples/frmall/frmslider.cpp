#include "frmslider.h"
#include "ui_frmslider.h"

#include "../../demo/slider/sliderselect/frmsliderselect.h"
#include "../../demo/slider/sliderrange/frmsliderrange.h"
#include "../../demo/slider/slidertip/frmslidertip.h"

frmSlider::frmSlider(QWidget *parent) : QWidget(parent), ui(new Ui::frmSlider)
{
    ui->setupUi(this);
    this->initForm();
}

frmSlider::~frmSlider()
{
    delete ui;
}

void frmSlider::initForm()
{
    ui->stackedWidget->addWidget(new frmSliderSelect);
    ui->stackedWidget->addWidget(new frmSliderRange);
    ui->stackedWidget->addWidget(new frmSliderTip);
}

void frmSlider::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
