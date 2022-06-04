#pragma execution_character_set("utf-8")

#include "frmgaugecar.h"
#include "ui_frmgaugecar.h"
#include "gaugecar.h"
#include "qpropertyanimation.h"
#include "qvariantanimation.h"
#include "qmetaobject.h"
#include "qdebug.h"

frmGaugeCar::frmGaugeCar(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeCar)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeCar::~frmGaugeCar()
{
    delete ui;
}

void frmGaugeCar::initForm()
{
    //定时属性动画
    animation = new QPropertyAnimation(ui->gaugeCar, "value");
    animation->setDuration(800);

    //拿到所有动画类型
    QMetaObject metaObject = QEasingCurve::staticMetaObject;
    QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("Type"));
    int count = QEasingCurve::NCurveTypes - 1;
    for (int i = 0; i < count; ++i) {
        ui->cboxAnimationType->addItem(metaEnum.key(i));
    }

    //设置默认的动画效果
    ui->cboxAnimationType->setCurrentIndex(ui->cboxAnimationType->findText("OutBounce"));

    ui->horizontalSlider->setValue(88);
    //ui->gaugeCar->setCircleWidth(30);
    ui->ckAnimation->setChecked(true);
    ui->cboxPointerStyle->setCurrentIndex(1);
}

void frmGaugeCar::on_cboxPieStyle_currentIndexChanged(int index)
{
    ui->gaugeCar->setPieStyle((GaugeCar::PieStyle)index);
}

void frmGaugeCar::on_cboxPointerStyle_currentIndexChanged(int index)
{
    ui->gaugeCar->setPointerStyle((GaugeCar::PointerStyle)index);
}

void frmGaugeCar::on_horizontalSlider_valueChanged(int value)
{
    //如果开启了动画则启动属性动画机制
    if (ui->ckAnimation->isChecked()) {
        animation->stop();
        animation->setStartValue(ui->gaugeCar->getValue());
        animation->setEndValue(value);
        animation->start();
    } else {
        ui->gaugeCar->setValue(value);
    }
}

void frmGaugeCar::on_cboxAnimationType_currentIndexChanged(int index)
{
    animation->setEasingCurve((QEasingCurve::Type)index);
}
