#pragma execution_character_set("utf-8")

#include "frmxtablewidget.h"
#include "ui_frmxtablewidget.h"

frmXTableWidget::frmXTableWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmXTableWidget)
{
    ui->setupUi(this);
    this->initForm();
}

frmXTableWidget::~frmXTableWidget()
{
    delete ui;
}

void frmXTableWidget::initForm()
{
    QStringList labels;
    labels << "测试列1" << "测试列2" << "测试列3";

    int rows = 5;
    int columns = labels.count();
    ui->tableWidget->setRowCount(rows);
    ui->tableWidget->setColumnCount(columns);
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    int rowHeight = 25;
    //行标题最小高度,等同于和默认行高一致
    ui->tableWidget->horizontalHeader()->setFixedHeight(rowHeight);
    //默认行高
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(rowHeight);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            QString text = QString("%1_%2").arg(i + 1).arg(j + 1);
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(text));
        }
    }
}
