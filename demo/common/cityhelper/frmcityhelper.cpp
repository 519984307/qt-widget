#pragma execution_character_set("utf-8")

#include "frmcityhelper.h"
#include "ui_frmcityhelper.h"
#include "cityhelper.h"
#include "qdebug.h"

#define jsonFile ":/font/city.json"
frmCityHelper::frmCityHelper(QWidget *parent) : QWidget(parent), ui(new Ui::frmCityHelper)
{
    ui->setupUi(this);
    this->initForm();
}

frmCityHelper::~frmCityHelper()
{
    delete ui;
}

void frmCityHelper::initForm()
{
    //添加省份到下拉框,市区和县城会自动联动
    QStringList province = CityHelper::getProvince(jsonFile);
    ui->cboxProvince->addItems(province);
    ui->listProvince->addItems(province);
}

void frmCityHelper::on_cboxProvince_currentIndexChanged(int)
{
    QString provinceName = ui->cboxProvince->currentText();
    QStringList city = CityHelper::getCity(jsonFile, provinceName);
    ui->cboxCity->clear();
    ui->cboxCity->addItems(city);
}

void frmCityHelper::on_cboxCity_currentIndexChanged(int)
{
    QString provinceName = ui->cboxProvince->currentText();
    QString cityName = ui->cboxCity->currentText();
    QStringList county = CityHelper::getCounty(jsonFile, provinceName, cityName);
    ui->cboxCounty->clear();
    ui->cboxCounty->addItems(county);
}

void frmCityHelper::on_listProvince_currentItemChanged(QListWidgetItem *, QListWidgetItem *)
{
    QListWidgetItem *item = ui->listProvince->currentItem();
    if (item == 0) {
        return;
    }

    QString provinceName = item->text();
    QStringList city = CityHelper::getCity(jsonFile, provinceName);
    ui->listCity->clear();
    ui->listCity->addItems(city);
    ui->listCity->setCurrentRow(0);
}

void frmCityHelper::on_listCity_currentItemChanged(QListWidgetItem *, QListWidgetItem *)
{
    QListWidgetItem *item1 = ui->listProvince->currentItem();
    QListWidgetItem *item2 = ui->listCity->currentItem();
    if (item1 == 0 || item2 == 0) {
        return;
    }

    QString provinceName = item1->text();
    QString cityName = item2->text();
    QStringList county = CityHelper::getCounty(jsonFile, provinceName, cityName);
    ui->listCounty->clear();
    ui->listCounty->addItems(county);
}
