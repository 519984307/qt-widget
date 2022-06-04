#pragma execution_character_set("utf-8")

#include "frmvideo.h"
#include "ui_frmvideo.h"

#include "../../demo/video/videobox/frmvideobox.h"
#include "../../demo/video/videopanel/frmvideopanel.h"
#include "../../demo/video/videoplayback/frmvideoplayback.h"
#include "../../demo/video/videowidget/frmvideowidget.h"

frmVideo::frmVideo(QWidget *parent) : QWidget(parent), ui(new Ui::frmVideo)
{
    ui->setupUi(this);
    this->initForm();
}

frmVideo::~frmVideo()
{
    delete ui;
}

void frmVideo::initForm()
{
    ui->stackedWidget->addWidget(new frmVideoBox);
    ui->stackedWidget->addWidget(new frmVideoPanel);
    ui->stackedWidget->addWidget(new frmVideoPlayback);
    ui->stackedWidget->addWidget(new frmVideoWidget);
}

void frmVideo::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
