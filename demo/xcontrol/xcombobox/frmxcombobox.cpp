#pragma execution_character_set("utf-8")

#include "frmxcombobox.h"
#include "ui_frmxcombobox.h"

frmXComboBox::frmXComboBox(QWidget *parent) : QWidget(parent), ui(new Ui::frmXComboBox)
{
    ui->setupUi(this);
    this->initForm();
}

frmXComboBox::~frmXComboBox()
{
    delete ui;
}

void frmXComboBox::initForm()
{
    QStringList items;
    items << "1hello" << "2hello123456" << "3helloabcdefghijklmnopqrstuvw";

    //指定宽度,不自动计算下拉选项宽度
    ui->xcomboBox1->setAutoWidth(false);
    ui->xcomboBox1->setItemWidth(300);
    ui->xcomboBox1->addItems(items);

    //指定高度,自动计算下拉选项宽度
    ui->xcomboBox2->setAutoWidth(true);
    ui->xcomboBox2->setItemHeight(30);
    ui->xcomboBox2->addItems(items);
}
