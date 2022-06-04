#pragma execution_character_set("utf-8")

#include "frmgaugeclock.h"
#include "ui_frmgaugeclock.h"

frmGaugeClock::frmGaugeClock(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeClock)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeClock::~frmGaugeClock()
{
    delete ui;
}

void frmGaugeClock::initForm()
{
#if 1
    ui->gaugeClock2->setCrownColorStart(QColor(205, 214, 223));
    ui->gaugeClock2->setCrownColorEnd(QColor(39, 75, 105).lighter(150));
    ui->gaugeClock2->setForeground(QColor(151, 186, 202));
    ui->gaugeClock2->setBackground(QColor(39, 75, 105));
    ui->gaugeClock2->setPointerHourColor(QColor(197, 214, 222));
    ui->gaugeClock2->setPointerMinColor(QColor(197, 214, 222));
    ui->gaugeClock2->setPointerSecColor(QColor(99, 133, 152));
    ui->gaugeClock2->setSecondStyle(GaugeClock::SecondStyle_Spring);
#else
    ui->gaugeClock2->setCrownColorStart("#3C3C3C");
    ui->gaugeClock2->setCrownColorEnd("#3C3C3C");
    ui->gaugeClock2->setForeground("#464646");
    ui->gaugeClock2->setBackground("#FFFFFF");
    ui->gaugeClock2->setPointerHourColor("#C0911F");
    ui->gaugeClock2->setPointerMinColor("#C0911F");
    ui->gaugeClock2->setPointerSecColor("#C0911F");
    ui->gaugeClock2->setSecondStyle(GaugeClock::SecondStyle_Continue);
#endif
}
