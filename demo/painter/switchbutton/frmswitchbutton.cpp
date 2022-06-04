#pragma execution_character_set("utf-8")

#include "frmswitchbutton.h"
#include "ui_frmswitchbutton.h"
#include "switchbutton.h"
#include "qdebug.h"

#define color1 QColor(34, 163, 169)
#define color2 QColor(162, 121, 197)
#define color3 QColor(255, 107, 107)
#define color4 QColor(72, 103, 149)

frmSwitchButton::frmSwitchButton(QWidget *parent) : QWidget(parent), ui(new Ui::frmSwitchButton)
{
    ui->setupUi(this);
    this->initForm();
}

frmSwitchButton::~frmSwitchButton()
{
    delete ui;
}

void frmSwitchButton::initForm()
{
    this->initBtn1();
    this->initBtn2();
    this->initBtn3();
    this->initSlot();
}

void frmSwitchButton::initBtn1()
{
    ui->switchButton11->setBgColorOn(color1);
    ui->switchButton12->setBgColorOn(color2);
    ui->switchButton13->setBgColorOn(color3);
    ui->switchButton14->setBgColorOn(color4);

    ui->switchButton11->setShowText(false);
    ui->switchButton12->setShowText(false);
    ui->switchButton13->setShowText(true);
    ui->switchButton14->setShowText(true);
    ui->switchButton12->setShowCircle(true);
    ui->switchButton14->setAnimation(true);
    ui->switchButton12->setChecked(true);
    ui->switchButton14->setChecked(true);

    ui->switchButton13->setTextOff("停止");
    ui->switchButton13->setTextOn("启动");
    ui->switchButton14->setTextOff("禁用");
    ui->switchButton14->setTextOn("启用");

    ui->switchButton15->setChecked(true);
    ui->switchButton15->setEnabled(false);
}

void frmSwitchButton::initBtn2()
{
    ui->switchButton21->setButtonStyle(SwitchButton::ButtonStyle_Rect);
    ui->switchButton22->setButtonStyle(SwitchButton::ButtonStyle_Rect);
    ui->switchButton23->setButtonStyle(SwitchButton::ButtonStyle_Rect);
    ui->switchButton24->setButtonStyle(SwitchButton::ButtonStyle_Rect);
    ui->switchButton25->setButtonStyle(SwitchButton::ButtonStyle_Rect);

    ui->switchButton21->setBgColorOn(color1);
    ui->switchButton22->setBgColorOn(color2);
    ui->switchButton23->setBgColorOn(color3);
    ui->switchButton24->setBgColorOn(color4);

    ui->switchButton21->setShowText(false);
    ui->switchButton22->setShowText(false);
    ui->switchButton23->setShowText(true);
    ui->switchButton24->setShowText(true);
    ui->switchButton22->setShowCircle(true);
    ui->switchButton24->setAnimation(true);
    ui->switchButton22->setChecked(true);
    ui->switchButton24->setChecked(true);

    ui->switchButton23->setTextOff("停止");
    ui->switchButton23->setTextOn("启动");
    ui->switchButton24->setTextOff("禁用");
    ui->switchButton24->setTextOn("启用");

    ui->switchButton25->setChecked(false);
    ui->switchButton25->setEnabled(false);
}

void frmSwitchButton::initBtn3()
{
    ui->switchButton31->setButtonStyle(SwitchButton::ButtonStyle_CircleOut);
    ui->switchButton32->setButtonStyle(SwitchButton::ButtonStyle_CircleOut);
    ui->switchButton33->setButtonStyle(SwitchButton::ButtonStyle_CircleOut);
    ui->switchButton34->setButtonStyle(SwitchButton::ButtonStyle_CircleOut);
    ui->switchButton35->setButtonStyle(SwitchButton::ButtonStyle_CircleOut);

    int space = 8;
    ui->switchButton31->setSpace(space);
    ui->switchButton32->setSpace(space);
    ui->switchButton33->setSpace(space);
    ui->switchButton34->setSpace(space);
    ui->switchButton35->setSpace(space);

    int radius = 8;
    ui->switchButton31->setRectRadius(radius);
    ui->switchButton32->setRectRadius(radius);
    ui->switchButton33->setRectRadius(radius);
    ui->switchButton34->setRectRadius(radius);
    ui->switchButton35->setRectRadius(radius);

    ui->switchButton31->setBgColorOn(color1);
    ui->switchButton32->setBgColorOn(color2);
    ui->switchButton33->setBgColorOn(color3);
    ui->switchButton34->setBgColorOn(color4);
    ui->switchButton35->setBgColorOn(color4);

    ui->switchButton31->setSliderColorOn(color1);
    ui->switchButton32->setSliderColorOn(color2);
    ui->switchButton33->setSliderColorOn(color3);
    ui->switchButton34->setSliderColorOn(color4);
    ui->switchButton35->setSliderColorOn(color4);

    ui->switchButton31->setShowText(false);
    ui->switchButton32->setShowText(false);
    ui->switchButton33->setShowText(true);
    ui->switchButton34->setShowText(true);
    ui->switchButton34->setAnimation(true);
    ui->switchButton32->setChecked(true);
    ui->switchButton34->setChecked(true);

    ui->switchButton35->setChecked(true);
    ui->switchButton35->setEnabled(false);
}

void frmSwitchButton::initSlot()
{
    //关联信号槽
#if 1
    connect(ui->switchButton11, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));
    connect(ui->switchButton12, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));
    connect(ui->switchButton13, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));
    connect(ui->switchButton14, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));
    connect(ui->switchButton21, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));
    connect(ui->switchButton22, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));
    connect(ui->switchButton23, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));
    connect(ui->switchButton24, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));
    connect(ui->switchButton31, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));
    connect(ui->switchButton32, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));
    connect(ui->switchButton33, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));
    connect(ui->switchButton34, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));
#else
    QList<SwitchButton *> btns = this->findChildren<SwitchButton *>();
    foreach (SwitchButton *btn, btns) {
        connect(btn, SIGNAL(checkedChanged(bool)), this, SLOT(checkedChanged(bool)));
    }
#endif
}

void frmSwitchButton::checkedChanged(bool checked)
{
    SwitchButton *btn = (SwitchButton *)sender();
    QString info = QString("按钮: %1  状态: %2").arg(btn->objectName()).arg(checked ? "打开" : "关闭");
    ui->labInfo->setText(info);
}
