#pragma execution_character_set("utf-8")

#include "frmnavbuttongroup.h"
#include "ui_frmnavbuttongroup.h"
#include "qpushbutton.h"
#include "qtimer.h"

frmNavButtonGroup::frmNavButtonGroup(QWidget *parent) : QWidget(parent), ui(new Ui::frmNavButtonGroup)
{
    ui->setupUi(this);
    this->initForm();
    QTimer::singleShot(1000, this, SLOT(setIndex()));
}

frmNavButtonGroup::~frmNavButtonGroup()
{
    delete ui;
}

void frmNavButtonGroup::initForm()
{
    //ui->buttonGroup1->clearButton();
    ui->buttonGroup2->clearButton();
    ui->buttonGroup3->clearButton();
    ui->buttonGroup4->clearButton();

    QStringList list;
    list << "学生管理" << "教师管理" << "成绩管理" << "成绩查询" << "系统设置";
    int count = list.count();

    for (int i = 0; i < count; i++) {
        QPushButton *btn = new QPushButton;
        btn->setCheckable(true);
        btn->setText(list.at(i));
        btn->setMinimumHeight(30);
        //btn->setFixedSize(80, 30);
        //ui->buttonGroup1->addButton((QAbstractButton *)btn, i);
    }

    for (int i = 0; i < count; i++) {
        QPushButton *btn = new QPushButton;
        btn->setCheckable(true);
        btn->setText(list.at(i));
        btn->setMinimumHeight(30);
        //btn->setFixedSize(80, 30);
        ui->buttonGroup2->addButton((QAbstractButton *)btn, i);
    }

    for (int i = 0; i < count; i++) {
        QPushButton *btn = new QPushButton;
        btn->setCheckable(true);
        btn->setText(list.at(i));
        btn->setMinimumHeight(30);
        ui->buttonGroup3->addButton((QAbstractButton *)btn, i);
    }

    for (int i = 0; i < count; i++) {
        QPushButton *btn = new QPushButton;
        btn->setCheckable(true);
        btn->setText(list.at(i));
        btn->setMinimumHeight(30);
        ui->buttonGroup4->addButton((QAbstractButton *)btn, i);
    }

    ui->buttonGroup2->setBaseColor(QColor(23, 160, 134));
    ui->buttonGroup3->setBaseColor(QColor(40, 45, 48), true);
    ui->buttonGroup4->setBaseColor(QColor(214, 77, 84), true);

    //ui->buttonGroup2->setTextNormalColor(QColor(255,255,255));
    ui->buttonGroup3->setTextNormalColor(QColor(255, 255, 255));
    ui->buttonGroup4->setTextNormalColor(QColor(255, 255, 255));

    ui->buttonGroup1->setLinePosition(NavButtonGroup::LinePosition_Top);
    ui->buttonGroup2->setLinePosition(NavButtonGroup::LinePosition_Bottom);
    ui->buttonGroup3->setLinePosition(NavButtonGroup::LinePosition_Left);
    ui->buttonGroup4->setLinePosition(NavButtonGroup::LinePosition_Right);

    //ui->buttonGroup1->addFinsh();
    //ui->buttonGroup2->addFinsh();
    ui->buttonGroup3->addFinsh();
    ui->buttonGroup4->addFinsh();

    ui->buttonGroup1->setFixedHeight(33);
    ui->buttonGroup2->setFixedHeight(33);
    ui->buttonGroup3->setFixedWidth(100);
    ui->buttonGroup4->setFixedWidth(100);
}

void frmNavButtonGroup::setIndex()
{
    ui->buttonGroup1->setIndex(1);
    ui->buttonGroup2->setIndex(3);
    ui->buttonGroup3->setIndex(1);
    ui->buttonGroup4->setIndex(3);
}
