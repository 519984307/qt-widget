#pragma execution_character_set("utf-8")

#include "frmyscrollbar.h"
#include "ui_frmyscrollbar.h"
#include "qdebug.h"

frmYScrollBar::frmYScrollBar(QWidget *parent) : QWidget(parent), ui(new Ui::frmYScrollBar)
{
    ui->setupUi(this);
    ui->vscrollbarButton->setScrollBar(ui->verticalScrollBar);
    ui->hscrollbarButton->setScrollBar(ui->horizontalScrollBar);
}

frmYScrollBar::~frmYScrollBar()
{
    delete ui;
}
