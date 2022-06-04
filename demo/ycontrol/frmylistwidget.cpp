#pragma execution_character_set("utf-8")

#include "frmylistwidget.h"
#include "ui_frmylistwidget.h"
#include "qdebug.h"

frmYListWidget::frmYListWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmYListWidget)
{
    ui->setupUi(this);    
    for (int i = 1; i <= 45; i++) {
        ui->listWidget->addItem(QString("AAAAAA%1").arg(i));
    }
}

frmYListWidget::~frmYListWidget()
{
    delete ui;
}
