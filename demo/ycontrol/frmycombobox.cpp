#pragma execution_character_set("utf-8")

#include "frmycombobox.h"
#include "ui_frmycombobox.h"
#include "qdebug.h"

frmYComboBox::frmYComboBox(QWidget *parent) : QWidget(parent), ui(new Ui::frmYComboBox)
{
    ui->setupUi(this);
    ui->comboBox->setMaxVisibleItems(11);
    for (int i = 1; i <= 45; i++) {
        ui->comboBox->addItem(QString("AAAAAA%1").arg(i));
    }
}

frmYComboBox::~frmYComboBox()
{
    delete ui;
}
