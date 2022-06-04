#pragma execution_character_set("utf-8")

#include "frmwavewater.h"
#include "ui_frmwavewater.h"
#include "qfiledialog.h"
#include "qapplication.h"

frmWaveWater::frmWaveWater(QWidget *parent) : QWidget(parent), ui(new Ui::frmWaveWater)
{
    ui->setupUi(this);
    this->initForm();
}

frmWaveWater::~frmWaveWater()
{
    delete ui;
}

void frmWaveWater::initForm()
{
    //loadImage(":/image/liuyifei4.jpg");
    loadImage(":/image/meinv1.jpg");
}

void frmWaveWater::loadImage(const QString &file)
{
    QPixmap pix(file);
    pix = pix.scaled(ui->waveWater->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->labFile->setText(file);
    ui->waveWater->setImage(pix);
}

void frmWaveWater::on_btnOpen_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "选择图像", qApp->applicationDirPath(), "图片文件(*.jpg *.png)");
    if (!file.isEmpty()) {
        loadImage(file);
    }
}
