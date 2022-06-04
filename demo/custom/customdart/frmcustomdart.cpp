#pragma execution_character_set("utf-8")

#include "frmcustomdart.h"
#include "ui_frmcustomdart.h"

frmCustomDart::frmCustomDart(QWidget *parent) : QWidget(parent), ui(new Ui::frmCustomDart)
{
    ui->setupUi(this);
    this->initForm();
}

frmCustomDart::~frmCustomDart()
{
    delete ui;
}

void frmCustomDart::initForm()
{
    ui->customDart2->setBgColor(QColor(117, 55, 117));
    ui->customDart2->setFanColor1(QColor(250, 250, 250));
    ui->customDart2->setFanColor2(QColor(193, 50, 86));

    ui->customDart2->setFanSize(15);
    ui->customDart2->setFanOffset(0);
    ui->customDart2->setFanCount(10);
    ui->customDart2->setFanText("A|B|C|D|E|F|G|H|I|J");
}
