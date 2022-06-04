#include "frmimage.h"
#include "ui_frmimage.h"

#include "../../demo/image/adswidget/frmadswidget.h"
#include "../../demo/image/adswidget2/frmadswidget2.h"
#include "../../demo/image/animationbutton/frmanimationbutton.h"
#include "../../demo/image/devicebutton/frmdevicebutton.h"
#include "../../demo/image/imageanimation/frmimageanimation.h"
#include "../../demo/image/imageeffect/frmimageeffect.h"
#include "../../demo/image/imageswitch/frmimageswitch.h"
#include "../../demo/image/imageview/frmimageview.h"
#include "../../demo/image/imagecalendar/frmimagecalendar.h"
#include "../../demo/image/imagepower/frmimagepower.h"
#include "../../demo/image/imageclock/frmimageclock.h"
#include "../../demo/image/imagepilot/frmimagepilot.h"

frmImage::frmImage(QWidget *parent) : QWidget(parent), ui(new Ui::frmImage)
{
    ui->setupUi(this);
    this->initForm();
}

frmImage::~frmImage()
{
    delete ui;
}

void frmImage::initForm()
{
    ui->stackedWidget->addWidget(new frmAdsWidget);
    ui->stackedWidget->addWidget(new frmAdsWidget2);
    ui->stackedWidget->addWidget(new frmAnimationButton);
    ui->stackedWidget->addWidget(new frmDeviceButton);
    ui->stackedWidget->addWidget(new frmImageAnimation);
    ui->stackedWidget->addWidget(new frmImageEffect);
    ui->stackedWidget->addWidget(new frmImageSwitch);
    ui->stackedWidget->addWidget(new frmImageView);
    ui->stackedWidget->addWidget(new frmImageCalendar);
    ui->stackedWidget->addWidget(new frmImagePower);
    ui->stackedWidget->addWidget(new frmImageClock);
    ui->stackedWidget->addWidget(new frmImagePilot);
}

void frmImage::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
