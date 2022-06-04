#include "frmcustom.h"
#include "ui_frmcustom.h"

#include "../../demo/custom/customgraphics/frmcustomgraphics.h"
#include "../../demo/custom/customrocker/frmcustomrocker.h"
#include "../../demo/custom/custompie/frmcustompie.h"
#include "../../demo/custom/customring/frmcustomring.h"
#include "../../demo/custom/customdart/frmcustomdart.h"
#include "../../demo/custom/scantantan/frmscantantan.h"
#include "../../demo/custom/spiderchart/frmspiderchart.h"
#include "../../demo/custom/shadowcalendar/frmshadowcalendar.h"
#include "../../demo/custom/shadowclock/frmshadowclock.h"
#include "../../demo/custom/shadowwidget/frmshadowwidget.h"
#include "../../demo/custom/tasktableview/frmtasktableview.h"
#include "../../demo/custom/timeaxis/frmtimeaxis.h"
#include "../../demo/custom/timeline/frmtimeline.h"

frmCustom::frmCustom(QWidget *parent) : QWidget(parent), ui(new Ui::frmCustom)
{
    ui->setupUi(this);
    this->initForm();
}

frmCustom::~frmCustom()
{
    delete ui;
}

void frmCustom::initForm()
{
    ui->stackedWidget->addWidget(new frmCustomGraphics);
    ui->stackedWidget->addWidget(new frmCustomRocker);
    ui->stackedWidget->addWidget(new frmCustomPie);
    ui->stackedWidget->addWidget(new frmCustomRing);
    ui->stackedWidget->addWidget(new frmCustomDart);
    ui->stackedWidget->addWidget(new frmScanTanTan);
    ui->stackedWidget->addWidget(new frmSpiderChart);
    ui->stackedWidget->addWidget(new frmShadowCalendar);
    ui->stackedWidget->addWidget(new frmShadowClock);
    ui->stackedWidget->addWidget(new frmShadowWidget);
    ui->stackedWidget->addWidget(new frmTaskTableView);
    ui->stackedWidget->addWidget(new frmTimeAxis);
    ui->stackedWidget->addWidget(new frmTimeLine);
}

void frmCustom::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
