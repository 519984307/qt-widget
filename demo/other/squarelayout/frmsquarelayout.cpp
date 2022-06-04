#pragma execution_character_set("utf-8")

#include "frmsquarelayout.h"
#include "ui_frmsquarelayout.h"
#include "squarelayout.h"
#include "qboxlayout.h"
#include "qpushbutton.h"

frmSquareLayout::frmSquareLayout(QWidget *parent) : QWidget(parent), ui(new Ui::frmSquareLayout)
{
    ui->setupUi(this);
    this->initForm();
}

frmSquareLayout::~frmSquareLayout()
{
    delete ui;
}

void frmSquareLayout::initForm()
{
    QLayout *layout;
#if 1
    //在该布局中的控件永远正方形
    layout = new SquareLayout;
#else
    //在该布局中自动拉伸填充
    layout = new QHBoxLayout;
#endif

    QPushButton *btn = new QPushButton;
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(btn);
    this->setLayout(layout);
}
