#include "frmpainter.h"
#include "ui_frmpainter.h"

#include "../../demo/painter/battery/frmbattery.h"
#include "../../demo/painter/lightbutton/frmlightbutton.h"
#include "../../demo/painter/lightpoint/frmlightpoint.h"
#include "../../demo/painter/magicmouse/frmmagicmouse.h"
#include "../../demo/painter/magicpenguin/frmmagicpenguin.h"
#include "../../demo/painter/magicfish/frmmagicfish.h"
#include "../../demo/painter/magicpool/frmmagicpool.h"
#include "../../demo/painter/magicpoolfish/frmmagicpoolfish.h"
#include "../../demo/painter/roundcircle/frmroundcircle.h"
#include "../../demo/painter/roundwidget/frmroundwidget.h"
#include "../../demo/painter/roundlogo/frmroundlogo.h"
#include "../../demo/painter/switchbutton/frmswitchbutton.h"
#include "../../demo/painter/oventimer/frmoventimer.h"
#include "../../demo/painter/tumbler/frmtumbler.h"
#include "../../demo/painter/tumbler/frmtumblerdatetime.h"
#include "../../demo/painter/lunarcalendarinfo/frmlunarcalendarinfo.h"
#include "../../demo/painter/lunarcalendarwidget/frmlunarcalendarwidget.h"
#include "../../demo/painter/tiledbg/frmtiledbg.h"
#include "../../demo/painter/telwidget/frmtelwidget.h"

frmPainter::frmPainter(QWidget *parent) : QWidget(parent), ui(new Ui::frmPainter)
{
    ui->setupUi(this);
    this->initForm();
}

frmPainter::~frmPainter()
{
    delete ui;
}

void frmPainter::initForm()
{
    ui->stackedWidget->addWidget(new frmBattery);
    ui->stackedWidget->addWidget(new frmLightButton);
    ui->stackedWidget->addWidget(new frmLightPoint);
    ui->stackedWidget->addWidget(new frmMagicMouse);
    ui->stackedWidget->addWidget(new frmMagicPenguin);
    ui->stackedWidget->addWidget(new frmMagicFish);
    ui->stackedWidget->addWidget(new frmMagicPool);
    ui->stackedWidget->addWidget(new frmMagicPoolFish);
    ui->stackedWidget->addWidget(new frmRoundCircle);
    ui->stackedWidget->addWidget(new frmRoundWidget);
    ui->stackedWidget->addWidget(new frmRoundLogo);
    ui->stackedWidget->addWidget(new frmSwitchButton);
    ui->stackedWidget->addWidget(new frmOvenTimer);
    ui->stackedWidget->addWidget(new frmTumbler);
    ui->stackedWidget->addWidget(new frmTumblerDateTime);
    ui->stackedWidget->addWidget(new frmLunarCalendarInfo);
    ui->stackedWidget->addWidget(new frmLunarCalendarWidget);
    ui->stackedWidget->addWidget(new frmTiledBg);
    ui->stackedWidget->addWidget(new frmTelWidget);
}

void frmPainter::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
