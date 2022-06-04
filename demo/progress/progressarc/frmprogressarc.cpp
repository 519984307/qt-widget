#pragma execution_character_set("utf-8")

#include "frmprogressarc.h"
#include "ui_frmprogressarc.h"

frmProgressArc::frmProgressArc(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgressArc)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressArc::~frmProgressArc()
{
    delete ui;
}

void frmProgressArc::initForm()
{
    //ui->progressArc1->setArcColor(QColor(41, 197, 90));
    ui->progressArc2->setArcColor(QColor(247, 74, 99));
    ui->progressArc3->setArcColor(QColor(25, 148, 255));
    //ui->progressArc4->setArcColor(QColor(41, 197, 90));
    ui->progressArc5->setArcColor(QColor(247, 74, 99));
    ui->progressArc6->setArcColor(QColor(25, 148, 255));

    //ui->progressArc1->setTextColor(QColor(41, 197, 90));
    ui->progressArc2->setTextColor(QColor(247, 74, 99));
    ui->progressArc3->setTextColor(QColor(25, 148, 255));
    //ui->progressArc4->setTextColor(QColor(41, 197, 90));
    ui->progressArc5->setTextColor(QColor(247, 74, 99));
    ui->progressArc6->setTextColor(QColor(25, 148, 255));

    ui->progressArc2->setStartAngle(135);
    ui->progressArc2->setEndAngle(-45);
    ui->progressArc5->setStartAngle(135);
    ui->progressArc5->setEndAngle(-45);

    ui->progressArc3->setStartAngle(0);
    ui->progressArc3->setEndAngle(0);
    ui->progressArc6->setStartAngle(0);
    ui->progressArc6->setEndAngle(0);

    ui->progressArc2->setTitle("错误率");
    ui->progressArc5->setTitle("错误率");
    ui->progressArc3->setTitle("完成率");
    ui->progressArc6->setTitle("完成率");

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressArc1, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressArc2, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressArc3, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressArc4, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressArc5, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressArc6, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
