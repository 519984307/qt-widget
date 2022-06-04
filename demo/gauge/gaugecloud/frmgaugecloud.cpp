#pragma execution_character_set("utf-8")

#include "frmgaugecloud.h"
#include "ui_frmgaugecloud.h"
#include "gaugecloud.h"
#include "qdebug.h"

frmGaugeCloud::frmGaugeCloud(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeCloud)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeCloud::~frmGaugeCloud()
{
    delete ui;
}

void frmGaugeCloud::initForm()
{
    connect(ui->gaugeCloud1, SIGNAL(mousePressed(int, QString)), this, SLOT(mousePressed(int, QString)));
    connect(ui->gaugeCloud2, SIGNAL(mousePressed(int, QString)), this, SLOT(mousePressed(int, QString)));
    connect(ui->gaugeCloud3, SIGNAL(mousePressed(int, QString)), this, SLOT(mousePressed(int, QString)));
    connect(ui->gaugeCloud4, SIGNAL(mousePressed(int, QString)), this, SLOT(mousePressed(int, QString)));

    connect(ui->gaugeCloud1, SIGNAL(mouseReleased(int, QString)), this, SLOT(mouseReleased(int, QString)));
    connect(ui->gaugeCloud2, SIGNAL(mouseReleased(int, QString)), this, SLOT(mouseReleased(int, QString)));
    connect(ui->gaugeCloud3, SIGNAL(mouseReleased(int, QString)), this, SLOT(mouseReleased(int, QString)));
    connect(ui->gaugeCloud4, SIGNAL(mouseReleased(int, QString)), this, SLOT(mouseReleased(int, QString)));

    ui->gaugeCloud2->setCloudStyle(GaugeCloud::CloudStyle_White);
    ui->gaugeCloud3->setCloudStyle(GaugeCloud::CloudStyle_Blue);
    ui->gaugeCloud4->setCloudStyle(GaugeCloud::CloudStyle_Purple);
}

void frmGaugeCloud::mousePressed(int position, const QString &strPosition)
{
    GaugeCloud *gaugeClound = (GaugeCloud *)sender();
    QString text = QString("当前按下了: %1 %2").arg(position).arg(strPosition);
    if (gaugeClound == ui->gaugeCloud1) {
        ui->labPosition1->setText(text);
    } else if (gaugeClound == ui->gaugeCloud2) {
        ui->labPosition2->setText(text);
    } else if (gaugeClound == ui->gaugeCloud3) {
        ui->labPosition3->setText(text);
    } else if (gaugeClound == ui->gaugeCloud4) {
        ui->labPosition4->setText(text);
    }

    qDebug() << "mousePressed" << position << strPosition;
}

void frmGaugeCloud::mouseReleased(int position, const QString &strPosition)
{
    qDebug() << "mouseReleased" << position << strPosition;
}
