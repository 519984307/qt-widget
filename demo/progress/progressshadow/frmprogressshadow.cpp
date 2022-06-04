#pragma execution_character_set("utf-8")

#include "frmprogressshadow.h"
#include "ui_frmprogressshadow.h"
#include "qpalette.h"

frmProgressShadow::frmProgressShadow(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgressShadow)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressShadow::~frmProgressShadow()
{
    delete ui;
}

void frmProgressShadow::initForm()
{
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QColor("#333645"));
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    ui->progressShadow2->setProgressColor(QColor("#0BA6AC"));
    ui->progressShadow3->setProgressColor(QColor("#A279C5"));
    ui->progressShadow5->setProgressColor(QColor("#0BA6AC"));
    ui->progressShadow6->setProgressColor(QColor("#A279C5"));

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressShadow1, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressShadow2, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressShadow3, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressShadow4, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressShadow5, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressShadow6, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
