#pragma execution_character_set("utf-8")

#include "frmimageeffect.h"
#include "ui_frmimageeffect.h"
#include "imageeffect.h"
#include "qfiledialog.h"
#include "qdebug.h"

frmImageEffect::frmImageEffect(QWidget *parent) : QWidget(parent), ui(new Ui::frmImageEffect)
{
    ui->setupUi(this);
    this->initForm();
}

frmImageEffect::~frmImageEffect()
{
    delete ui;
}

void frmImageEffect::showEvent(QShowEvent *)
{
    imageEffect();
}

void frmImageEffect::resizeEvent(QResizeEvent *)
{
    imageEffect();
}

void frmImageEffect::initForm()
{
    connect(ui->cboxFile, SIGNAL(currentIndexChanged(int)), this, SLOT(imageEffect()));
    connect(ui->cboxType, SIGNAL(currentIndexChanged(int)), this, SLOT(imageEffect()));

    ui->cboxFile->addItem(":/image/liuyifei.jpg");
    ui->cboxFile->addItem(":/image/liuyifei2.jpg");

    QStringList types;
    types << "原始图片" << "灰度效果" << "复古效果" << "红色蒙版" << "反转效果" << "变亮效果" << "变暗效果";
    ui->cboxType->addItems(types);
}

void frmImageEffect::imageEffect()
{
    if (!isVisible()) {
        return;
    }

    QImage img(ui->cboxFile->currentText());
    int index = ui->cboxType->currentIndex();

    if (index == 5) {
        img = ImageEffect::brightness(img, 70);
    } else if (index == 6) {
        img = ImageEffect::brightness(img, -70);
    } else {
        img = ImageEffect::effect(img, index, 0);
    }

    img = img.scaled(ui->labImage->size() - QSize(4, 4), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->labImage->setPixmap(QPixmap::fromImage(img));
}

void frmImageEffect::on_btnOpen_clicked()
{
    QString filter = "图片文件(*.png *.bmp *.jpg)";
    QString fileName = QFileDialog::getOpenFileName(this, "选择", qApp->applicationDirPath(), filter);
    if (!fileName.isEmpty()) {
        ui->cboxFile->addItem(fileName);
        ui->cboxFile->setCurrentIndex(ui->cboxFile->count() - 1);
    }
}
