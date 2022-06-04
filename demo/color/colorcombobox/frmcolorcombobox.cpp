#pragma execution_character_set("utf-8")

#include "frmcolorcombobox.h"
#include "ui_frmcolorcombobox.h"

frmColorComboBox::frmColorComboBox(QWidget *parent) : QWidget(parent), ui(new Ui::frmColorComboBox)
{
    ui->setupUi(this);
    this->initForm();
}

frmColorComboBox::~frmColorComboBox()
{
    delete ui;
}

void frmColorComboBox::initForm()
{
    ui->colorComboBox1->setIconSize(QSize(150, 16));
    ui->colorComboBox1->setShowColorName(false);
    ui->colorComboBox1->initItems();
    ui->colorComboBox2->initItems();
}
