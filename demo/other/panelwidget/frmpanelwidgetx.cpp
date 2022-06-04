#pragma execution_character_set("utf-8")

#include "frmpanelwidgetx.h"
#include "ui_frmpanelwidgetx.h"
#include "qdatetime.h"
#include "qtimer.h"
#include "qdebug.h"

frmPanelWidgetX::frmPanelWidgetX(QWidget *parent) :	QWidget(parent), ui(new Ui::frmPanelWidgetX)
{
    ui->setupUi(this);
    this->initForm();
}

frmPanelWidgetX::~frmPanelWidgetX()
{
    delete ui;
}

void frmPanelWidgetX::setFlag(const QString &flag)
{
    this->flag = flag;
}

QString frmPanelWidgetX::getFlag() const
{
    return this->flag;
}

void frmPanelWidgetX::setValue(int value)
{
    //只是举例
    ui->widget1->setLightGreen();
    ui->widget2->setLightGreen();
    ui->widget3->setLightGreen();
    ui->gaugeProgress->setValue(value);
}

int frmPanelWidgetX::getValue() const
{
    return (int)ui->gaugeProgress->getValue();
}

void frmPanelWidgetX::initForm()
{
    type = 0;
    flag = "0001";

    QTime t = QTime::currentTime();
    srand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    //timer->start();
    updateValue();
}

void frmPanelWidgetX::updateValue()
{
    if (type == 0) {
        ui->widget1->setLightGreen();
        ui->widget2->setLightRed();
        ui->widget3->setLightBlue();
        type = 1;
    } else if (type == 1) {
        ui->widget1->setLightBlue();
        ui->widget2->setLightGreen();
        ui->widget3->setLightRed();
        type = 2;
    } else if (type == 2) {
        ui->widget1->setLightRed();
        ui->widget2->setLightBlue();
        ui->widget3->setLightGreen();
        type = 0;
    }

    int value = rand() % 100;
    ui->gaugeProgress->setValue(value);
}
