#pragma execution_character_set("utf-8")

#include "frmanimationbutton.h"
#include "ui_frmanimationbutton.h"
#include "qdebug.h"

frmAnimationButton::frmAnimationButton(QWidget *parent) : QWidget(parent), ui(new Ui::frmAnimationButton)
{
    ui->setupUi(this);
    this->initForm();
}

frmAnimationButton::~frmAnimationButton()
{
    delete ui;
}

void frmAnimationButton::initForm()
{
    ui->animationButton1->setImageName(":/image/v-home-ico-contact.png");
    ui->animationButton2->setImageName(":/image/v-home-ico-home.png");
    ui->animationButton3->setImageName(":/image/v-home-ico-img.png");

    ui->animationButton4->setNormalImage(":/image/clean.png");
    ui->animationButton4->setEnterImage(":/image/clean_enter.png");
    ui->animationButton4->setLeaveImage(":/image/clean_leave.png");

    ui->animationButton5->setNormalImage(":/image/safe.png");
    ui->animationButton5->setEnterImage(":/image/safe_enter.png");
    ui->animationButton5->setLeaveImage(":/image/safe_leave.png");

    ui->animationButton6->setNormalImage(":/image/youhua.png");
    ui->animationButton6->setEnterImage(":/image/youhua_enter.png");
    ui->animationButton6->setLeaveImage(":/image/youhua_leave.png");

    connect(ui->animationButton1, SIGNAL(pressed()), this, SLOT(pressed()));
    connect(ui->animationButton2, SIGNAL(pressed()), this, SLOT(pressed()));
    connect(ui->animationButton3, SIGNAL(pressed()), this, SLOT(pressed()));
    connect(ui->animationButton4, SIGNAL(pressed()), this, SLOT(pressed()));
    connect(ui->animationButton5, SIGNAL(pressed()), this, SLOT(pressed()));
    connect(ui->animationButton6, SIGNAL(pressed()), this, SLOT(pressed()));

    connect(ui->animationButton1, SIGNAL(released()), this, SLOT(released()));
    connect(ui->animationButton2, SIGNAL(released()), this, SLOT(released()));
    connect(ui->animationButton3, SIGNAL(released()), this, SLOT(released()));
    connect(ui->animationButton4, SIGNAL(released()), this, SLOT(released()));
    connect(ui->animationButton5, SIGNAL(released()), this, SLOT(released()));
    connect(ui->animationButton6, SIGNAL(released()), this, SLOT(released()));

    connect(ui->animationButton1, SIGNAL(clicked()), this, SLOT(clicked()));
    connect(ui->animationButton2, SIGNAL(clicked()), this, SLOT(clicked()));
    connect(ui->animationButton3, SIGNAL(clicked()), this, SLOT(clicked()));
    connect(ui->animationButton4, SIGNAL(clicked()), this, SLOT(clicked()));
    connect(ui->animationButton5, SIGNAL(clicked()), this, SLOT(clicked()));
    connect(ui->animationButton6, SIGNAL(clicked()), this, SLOT(clicked()));
}

void frmAnimationButton::pressed()
{
    QString objName = sender()->objectName();
    qDebug() << objName << "pressed";
}

void frmAnimationButton::released()
{
    QString objName = sender()->objectName();
    qDebug() << objName << "released";
}

void frmAnimationButton::clicked()
{
    QString objName = sender()->objectName();
    qDebug() << objName << "clicked";
}
