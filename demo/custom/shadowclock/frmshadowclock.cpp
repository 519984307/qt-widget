#pragma execution_character_set("utf-8")

#include "frmshadowclock.h"
#include "ui_frmshadowclock.h"

frmShadowClock::frmShadowClock(QWidget *parent) : QWidget(parent), ui(new Ui::frmShadowClock)
{
    ui->setupUi(this);
    this->initForm();
}

frmShadowClock::~frmShadowClock()
{

}

void frmShadowClock::initForm()
{
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QColor("#2C3E50"));
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    ui->shadowClock1->setTextColor("#00FFFF");
    ui->shadowClock2->setTextColor("#FDC150");
    ui->shadowClock3->setTextColor("#FDA356");
    ui->shadowClock4->setTextColor("#EB766E");
    ui->shadowClock5->setTextColor("#A3DAD7");
    ui->shadowClock6->setTextColor("#9DBCFF");

    ui->shadowClock1->setShadowColor("#00FFFF");
    ui->shadowClock2->setShadowColor("#FDC150");
    ui->shadowClock3->setShadowColor("#FDA356");
    ui->shadowClock4->setShadowColor("#EB766E");
    ui->shadowClock5->setShadowColor("#A3DAD7");
    ui->shadowClock6->setShadowColor("#9DBCFF");
}
