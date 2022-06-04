#include "frmcommon.h"
#include "ui_frmcommon.h"

#include "../../demo/common/flatui/frmflatui.h"
#include "../../demo/common/zhtopy/frmzhtopy.h"
#include "../../demo/common/pinyin/frmpinyin.h"
#include "../../demo/common/ntpclient/frmntpclient.h"
#include "../../demo/common/savelog/frmsavelog.h"
#include "../../demo/common/saveruntime/frmsaveruntime.h"
#include "../../demo/common/trayicon/frmtrayicon.h"
#include "../../demo/common/smoothcurve/frmsmoothcurve.h"
#include "../../demo/common/base64helper/frmbase64helper.h"
#include "../../demo/common/iconhelper/frmiconhelper.h"
#include "../../demo/common/weather/frmweather.h"
#include "../../demo/common/cityhelper/frmcityhelper.h"

frmCommon::frmCommon(QWidget *parent) : QWidget(parent), ui(new Ui::frmCommon)
{
    ui->setupUi(this);
    this->initForm();
}

frmCommon::~frmCommon()
{
    delete ui;
}

void frmCommon::initForm()
{    
    ui->stackedWidget->addWidget(new frmFlatUI);
    ui->stackedWidget->addWidget(new frmZhToPY);
    ui->stackedWidget->addWidget(new frmPinYin);
    ui->stackedWidget->addWidget(new frmNtpClient);
    ui->stackedWidget->addWidget(new frmSaveLog);
    ui->stackedWidget->addWidget(new frmSaveRunTime);
    ui->stackedWidget->addWidget(new frmTrayIcon);
    ui->stackedWidget->addWidget(new frmSmoothCurve);
    ui->stackedWidget->addWidget(new frmBase64Helper);
    ui->stackedWidget->addWidget(new frmIconHelper);
    ui->stackedWidget->addWidget(new frmWeather);
    ui->stackedWidget->addWidget(new frmCityHelper);
}

void frmCommon::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
