#pragma execution_character_set("utf-8")

#include "frmnavpage.h"
#include "ui_frmnavpage.h"
#include "qtimer.h"

frmNavPage::frmNavPage(QWidget *parent) : QWidget(parent), ui(new Ui::frmNavPage)
{
    ui->setupUi(this);
    this->initForm();
}

frmNavPage::~frmNavPage()
{
    delete ui;
}

void frmNavPage::showEvent(QShowEvent *)
{
    static bool isLoad = false;
    if (!isLoad) {
        isLoad = true;
        this->initForm();
    }
}

void frmNavPage::initForm()
{
    //显示跳转按钮
    //ui->navPage3->setShowGoPage(true);
    //ui->navPage5->setShowGoPage(true);

    //设置对齐
    ui->navPage1->setNavPosition(NavPage::NavPosition_Left);
    ui->navPage3->setNavPosition(NavPage::NavPosition_Right);

    //设置颜色
    ui->navPage2->setDarkColor("#32B9CF", "#FFFFFF");
    ui->navPage3->setDarkColor("#A279C5", "#FFFFFF");
    ui->navPage4->setDarkColor("#8C2957", "#FFFFFF");
    ui->navPage5->setDarkColor("#04567E", "#FFFFFF");

    //设置页码按钮个数
    ui->navPage3->setPageButtonCount(3);
    ui->navPage4->setPageButtonCount(6);
    ui->navPage5->setPageButtonCount(3);

    //设置圆角角度
    ui->navPage4->setBorderRadius(19);
    ui->navPage5->setBorderRadius(19);
}
