#pragma execution_character_set("utf-8")

#include "frmyspinbox.h"
#include "ui_frmyspinbox.h"
#include "qdebug.h"

frmYSpinBox::frmYSpinBox(QWidget *parent) : QWidget(parent), ui(new Ui::frmYSpinBox)
{
    ui->setupUi(this);
}

frmYSpinBox::~frmYSpinBox()
{
    delete ui;
}
