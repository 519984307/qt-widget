#pragma execution_character_set("utf-8")

#include "frmytreewidget.h"
#include "ui_frmytreewidget.h"
#include "qdebug.h"

frmYTreeWidget::frmYTreeWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmYTreeWidget)
{
    ui->setupUi(this);
    this->initForm();
}

frmYTreeWidget::~frmYTreeWidget()
{
    delete ui;
}

void frmYTreeWidget::initForm()
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
