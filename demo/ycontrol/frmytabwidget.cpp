#pragma execution_character_set("utf-8")

#include "frmytabwidget.h"
#include "ui_frmytabwidget.h"
#include "qdebug.h"

frmYTabWidget::frmYTabWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmYTabWidget)
{
    ui->setupUi(this);
}

frmYTabWidget::~frmYTabWidget()
{
    delete ui;
}
