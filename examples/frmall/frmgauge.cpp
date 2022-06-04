#include "frmgauge.h"
#include "ui_frmgauge.h"

#include "../../demo/gauge/gaugecar/frmgaugecar.h"
#include "../../demo/gauge/gaugearc/frmgaugearc.h"
#include "../../demo/gauge/gaugepercent/frmgaugepercent.h"
#include "../../demo/gauge/gaugecircle/frmgaugecircle.h"
#include "../../demo/gauge/gaugeclock/frmgaugeclock.h"
#include "../../demo/gauge/gaugecompass/frmgaugecompass.h"
#include "../../demo/gauge/gaugecompass2/frmgaugecompass2.h"
#include "../../demo/gauge/gaugecompasspan/frmgaugecompasspan.h"
#include "../../demo/gauge/gaugedial/frmgaugedial.h"
#include "../../demo/gauge/gaugemini/frmgaugemini.h"
#include "../../demo/gauge/gaugenet/frmgaugenet.h"
#include "../../demo/gauge/gaugeplane/frmgaugeplane.h"
#include "../../demo/gauge/gaugeprogress/frmgaugeprogress.h"
#include "../../demo/gauge/gaugerange/frmgaugerange.h"
#include "../../demo/gauge/gaugeround/frmgaugeround.h"
#include "../../demo/gauge/gaugesimple/frmgaugesimple.h"
#include "../../demo/gauge/gaugespeed/frmgaugespeed.h"
#include "../../demo/gauge/gaugewatch/frmgaugewatch.h"
#include "../../demo/gauge/gaugelpm/frmgaugelpm.h"
#include "../../demo/gauge/gaugecolor/frmgaugecolor.h"
#include "../../demo/gauge/gaugecloud/frmgaugecloud.h"
#include "../../demo/gauge/gaugeweather/frmgaugeweather.h"
#include "../../demo/gauge/gaugedecibel/frmgaugedecibel.h"
#include "../../demo/gauge/gaugepanel/frmgaugepanel.h"
#include "../../demo/gauge/gaugeedit/frmgaugeedit.h"

frmGauge::frmGauge(QWidget *parent) : QWidget(parent), ui(new Ui::frmGauge)
{
    ui->setupUi(this);
    this->initForm();
}

frmGauge::~frmGauge()
{
    delete ui;
}

void frmGauge::initForm()
{
    ui->stackedWidget->addWidget(new frmGaugeCar);
    ui->stackedWidget->addWidget(new frmGaugeArc);
    ui->stackedWidget->addWidget(new frmGaugePercent);
    ui->stackedWidget->addWidget(new frmGaugeCircle);
    ui->stackedWidget->addWidget(new frmGaugeProgress);
    ui->stackedWidget->addWidget(new frmGaugeRange);
    ui->stackedWidget->addWidget(new frmGaugeSpeed);
    ui->stackedWidget->addWidget(new frmGaugeClock);
    ui->stackedWidget->addWidget(new frmGaugeNet);
    ui->stackedWidget->addWidget(new frmGaugeSimple);
    ui->stackedWidget->addWidget(new frmGaugeWatch);
    ui->stackedWidget->addWidget(new frmGaugeCompass);
    ui->stackedWidget->addWidget(new frmGaugeCompass2);
    ui->stackedWidget->addWidget(new frmGaugeCompassPan);
    ui->stackedWidget->addWidget(new frmGaugeDial);
    ui->stackedWidget->addWidget(new frmGaugeMini);
    ui->stackedWidget->addWidget(new frmGaugeRound);
    ui->stackedWidget->addWidget(new frmGaugePlane);
    ui->stackedWidget->addWidget(new frmGaugeLpm);
    ui->stackedWidget->addWidget(new frmGaugeColor);
    ui->stackedWidget->addWidget(new frmGaugeCloud);
    ui->stackedWidget->addWidget(new frmGaugeWeather);
    ui->stackedWidget->addWidget(new frmGaugeDecibel);
    ui->stackedWidget->addWidget(new frmGaugePanel);
    ui->stackedWidget->addWidget(new frmGaugeEdit);
}

void frmGauge::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
