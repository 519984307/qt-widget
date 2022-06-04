#pragma execution_character_set("utf-8")

#include "frmmagicpenguin.h"
#include "ui_frmmagicpenguin.h"

frmMagicPenguin::frmMagicPenguin(QWidget *parent) : QWidget(parent), ui(new Ui::frmMagicPenguin)
{
    ui->setupUi(this);
    this->initForm();
}

frmMagicPenguin::~frmMagicPenguin()
{
    delete ui;
}

void frmMagicPenguin::initForm()
{
    //ui->horizontalSlider->setRange(0, 360);
    //connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->magicMouse, SLOT(setAngle(int)));
}
