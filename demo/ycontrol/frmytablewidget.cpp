#pragma execution_character_set("utf-8")

#include "frmytablewidget.h"
#include "ui_frmytablewidget.h"
#include "qdatetime.h"
#include "qdebug.h"

frmYTableWidget::frmYTableWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmYTableWidget)
{
    ui->setupUi(this);
    this->initForm();
}

frmYTableWidget::~frmYTableWidget()
{
    delete ui;
}

void frmYTableWidget::initForm()
{
    QStringList headText;
    headText << "设备编号" << "设备名称" << "设备地址" << "告警内容" << "告警时间";
    QList<int> widths;
    widths << 80 << 150 << 80 << 180 << 250;
    ui->tableWidget->setColumnCount(headText.count());
    for (int i = 0; i < headText.count(); i++) {
        ui->tableWidget->setColumnWidth(i, widths.at(i));
    }

    ui->tableWidget->setHorizontalHeaderLabels(headText);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setMinimumHeight(35);

    ui->tableWidget->setRowCount(300);
    for (int i = 0; i < 300; i++) {
        QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString("测试设备%1").arg(i + 1));
        QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem *itemContent = new QTableWidgetItem("防区告警");
        QTableWidgetItem *itemTime = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        itemDeviceID->setTextAlignment(Qt::AlignCenter);
        itemDeviceName->setTextAlignment(Qt::AlignCenter);
        itemDeviceAddr->setTextAlignment(Qt::AlignCenter);
        itemContent->setTextAlignment(Qt::AlignCenter);
        itemTime->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget->setItem(i, 0, itemDeviceID);
        ui->tableWidget->setItem(i, 1, itemDeviceName);
        ui->tableWidget->setItem(i, 2, itemDeviceAddr);
        ui->tableWidget->setItem(i, 3, itemContent);
        ui->tableWidget->setItem(i, 4, itemTime);
    }
}
