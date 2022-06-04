#pragma execution_character_set("utf-8")

#include "frmycontrolall.h"
#include "ui_frmycontrolall.h"
#include "ycontrol.h"
#include "qdatetime.h"
#include "qdebug.h"

frmYControlAll::frmYControlAll(QWidget *parent) : QWidget(parent), ui(new Ui::frmYControlAll)
{
    ui->setupUi(this);
    this->initForm();
    this->initTree();
    this->initTable();
    YControl::initStyle(this);
}

frmYControlAll::~frmYControlAll()
{
    delete ui;
}

void frmYControlAll::initForm()
{
    ui->comboBox->setMaxVisibleItems(11);
    for (int i = 1; i <= 45; i++) {
        ui->comboBox->addItem(QString("AAAAAA%1").arg(i));
    }

    //ui->listWidget->verticalScrollBar()->hide();
    for (int i = 1; i <= 45; i++) {
        ui->listWidget->addItem(QString("AAAAAA%1").arg(i));
    }

    ui->vscrollbarButton->setScrollBar(ui->verticalScrollBar);
    ui->hscrollbarButton->setScrollBar(ui->horizontalScrollBar);
}

void frmYControlAll::initTree()
{
    ui->treeWidget->clear();
    ui->treeWidget->setHeaderLabel(" 树状列表控件");

    QTreeWidgetItem *group1 = new QTreeWidgetItem(ui->treeWidget);
    group1->setText(0, "父元素1");
    group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group1->setCheckState(0, Qt::PartiallyChecked);

    for (int i = 0; i < 3; ++i) {
        QTreeWidgetItem *item = new QTreeWidgetItem(group1);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        item->setText(0, QString("子元素%1").arg(i + 1));
        item->setCheckState(0, i < 1 ? Qt::Checked : Qt::Unchecked);
    }

    QTreeWidgetItem *group2 = new QTreeWidgetItem(ui->treeWidget);
    group2->setText(0, "父元素2");
    group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group2->setCheckState(0, Qt::Unchecked);

    for (int i = 1; i <= 15; i++) {
        QTreeWidgetItem *subItem21 = new QTreeWidgetItem(group2);
        subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem21->setText(0, QString("子元素%1").arg(i));
        subItem21->setCheckState(0, Qt::Unchecked);
    }

    ui->treeWidget->expandAll();
}

void frmYControlAll::initTable()
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
