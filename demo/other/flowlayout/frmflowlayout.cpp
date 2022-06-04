#pragma execution_character_set("utf-8")

#include "frmflowlayout.h"
#include "ui_frmflowlayout.h"
#include "flowlayout.h"
#include "qpushbutton.h"

frmFlowLayout::frmFlowLayout(QWidget *parent) : QWidget(parent), ui(new Ui::frmFlowLayout)
{
    ui->setupUi(this);
    this->initForm();
}

frmFlowLayout::~frmFlowLayout()
{
    delete ui;
}

void frmFlowLayout::initForm()
{
    //在该布局中的控件自动宽高排列
    FlowLayout *layout = new FlowLayout;
    for (int i = 0; i < 50; i++) {
        QPushButton *btn = new QPushButton;
        btn->setText(QString::number(i + 1));
        layout->addWidget(btn);
    }

    setLayout(layout);
}
