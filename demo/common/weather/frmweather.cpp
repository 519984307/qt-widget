#pragma execution_character_set("utf-8")

#include "frmweather.h"
#include "ui_frmweather.h"
#include "cityhelper.h"
#include "qlineedit.h"
#include "qdebug.h"

#define jsonFile ":/font/city.json"
frmWeather::frmWeather(QWidget *parent) : QWidget(parent), ui(new Ui::frmWeather)
{
    ui->setupUi(this);
    this->initForm();
    this->initTable();
    this->initConfig();
}

frmWeather::~frmWeather()
{
    delete ui;
}

void frmWeather::initForm()
{
    //关联天气类的信号
    weather = new Weather(this);
    connect(weather, SIGNAL(debug(QString)), this, SLOT(debug(QString)));
    connect(weather, SIGNAL(error(QString)), this, SLOT(error(QString)));
    connect(weather, SIGNAL(receiveWeather(QString, QString, QString, QList<WeatherInfo>)),
            this, SLOT(receiveWeather(QString, QString, QString, QList<WeatherInfo>)));

    weather->setLabel(ui->labWeather, 4);
    //weather->start(60);
}

void frmWeather::initTable()
{
    QList<QString> columnNames;
    QList<int> columnWidths;
    columnNames << "日期" << "低温" << "高温" << "类型" << "天气" << "风力" << "风向";
    columnWidths << 110 << 60 << 60 << 60 << 60 << 60 << 80;

    int columnCount = columnNames.count();
    ui->tableWidget->setColumnCount(columnCount);
    ui->tableWidget->setHorizontalHeaderLabels(columnNames);
    for (int i = 0; i < columnCount; i++) {
        ui->tableWidget->setColumnWidth(i, columnWidths.at(i));
    }

    //其他属性设置
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setFixedHeight(25);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    iconFont = Weather::getIconFont();
}

void frmWeather::initConfig()
{
    //添加省份到下拉框,市区和县城会自动联动
    QStringList province = CityHelper::getProvince(jsonFile);
    ui->cboxProvince->addItems(province);

    QStringList intervals;
    intervals << "不采集" << "1分钟" << "3分钟" << "5分钟" << "10分钟" << "20分钟" << "30分钟" << "60分钟";
    ui->cboxInterval->addItems(intervals);
    ui->cboxInterval->setCurrentIndex(7);

    QStringList styles;
    styles << "不显示" << "样式1" << "样式2" << "样式3" << "样式4";
    ui->cboxStyle->addItems(styles);
    ui->cboxStyle->setCurrentIndex(4);

    connect(ui->cboxName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(saveConfig()));
    connect(ui->cboxInterval, SIGNAL(currentIndexChanged(int)), this, SLOT(saveConfig()));
    connect(ui->cboxStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(saveConfig()));
}

void frmWeather::saveConfig()
{
    if (!isVisible()) {
        return;
    }

    QString city = ui->cboxName->currentText().trimmed();
    QString strInterval = ui->cboxInterval->currentText();
    int interval = strInterval.mid(0, strInterval.length() - 2).toInt();
    int style = ui->cboxStyle->currentIndex();
    emit configChanged(city, interval, style);
    //qDebug() << city << interval << style;

    weather->setLabel(ui->labWeather, style);
    //weather->start(interval);
    weather->query();
}

void frmWeather::debug(const QString &msg)
{
    ui->textEdit->setText(msg);
}

void frmWeather::error(const QString &msg)
{
    ui->textEdit->setText(msg);
}

void frmWeather::receiveWeather(const QString &city, const QString &wendu, const QString &ganmao, const QList<WeatherInfo> &weatherInfos)
{
    QStringList list;
    list << QString("城市: %1").arg(city);
    list << QString("温度: %1").arg(wendu);
    list << QString("提示: %1").arg(ganmao);
    ui->txtMsg->setText(list.join("\n"));

    //数据转成表格显示
    int count = weatherInfos.count();
    ui->tableWidget->setRowCount(count);
    for (int i = 0; i < count; ++i) {
        WeatherInfo weatherInfo = weatherInfos.at(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(weatherInfo.date));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(weatherInfo.low));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(weatherInfo.high));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(weatherInfo.type));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(weatherInfo.fengli));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(weatherInfo.fengxiang));

        //查找对应天气图标
        int icon = Weather::getWeatherIcon(weatherInfo.type);
        QTableWidgetItem *itemType = new QTableWidgetItem((QChar)icon);
        iconFont.setPixelSize(18);
        itemType->setFont(iconFont);
        ui->tableWidget->setItem(i, 4, itemType);
    }


    if (count > 1) {
        //今天特殊颜色显示
        for (int i = 0; i <= 6; ++i) {
            //ui->tableWidget->item(1, i)->setBackground(QColor("#22A3A9"));
            //ui->tableWidget->item(1, i)->setForeground(QColor("#FFFFFF"));
        }

        //所有居中
        for (int i = 0; i < count; ++i) {
            for (int j = 0; j <= 6; ++j) {
                ui->tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
            }
        }

        //今天的天气大图标
        int icon = Weather::getWeatherIcon(weatherInfos.at(1).type);
        iconFont.setPixelSize(100);
        ui->labType->setFont(iconFont);
        ui->labType->setText((QChar)icon);
    }
}

void frmWeather::on_btnQuery_clicked()
{
    ui->txtMsg->clear();
    ui->tableWidget->clearContents();
    QString city = ui->cboxName->currentText();
    weather->query(city);
}

void frmWeather::on_btnLocation_clicked()
{
    QString location = weather->getLocation();
    ui->textEdit->setText(location);

    location.replace("\"", "");
    location.replace("};", "");
    QStringList list = location.split(":");
    location = list.last();
    location = location.trimmed();
    ui->txtMsg->setText(location);

    //自动设置到下拉框
    if (location.contains("省")) {
        list = location.split("省");
        QString province = list.at(0);
        QString city = list.at(1);
        city.replace("市", "");
        ui->cboxName->lineEdit()->setText(city);
        on_btnQuery_clicked();
    }
}

void frmWeather::on_cboxProvince_currentIndexChanged(int)
{
    QString provinceName = ui->cboxProvince->currentText();
    QStringList city = CityHelper::getCity(jsonFile, provinceName);
    ui->cboxCity->clear();
    ui->cboxCity->addItems(city);
}

void frmWeather::on_cboxCity_currentIndexChanged(int)
{
    QString provinceName = ui->cboxProvince->currentText();
    QString cityName = ui->cboxCity->currentText();
    QStringList county = CityHelper::getCounty(jsonFile, provinceName, cityName);
    ui->cboxCounty->clear();
    ui->cboxCounty->addItems(county);
}

void frmWeather::on_cboxCounty_currentIndexChanged(int)
{
    //QString provinceName = ui->cboxProvince->currentText();
    //QString cityName = ui->cboxCity->currentText();
    //QString countyName = ui->cboxCounty->currentText();
    //QString name = QString("%1%2%3").arg(provinceName).arg(cityName).arg(countyName);
    QString name = ui->cboxCounty->currentText();
    if (name.startsWith("澳门")) {
        name = "澳门";
    }

    ui->cboxName->lineEdit()->setText(name);
    on_btnQuery_clicked();
}

void frmWeather::setConfig(const QString &city, int interval, int style)
{
    ui->cboxName->lineEdit()->setText(city);
    QString strInterval = QString("%1分钟").arg(interval);
    int index = ui->cboxInterval->findText(strInterval);
    ui->cboxInterval->setCurrentIndex(index < 0 ? 0 : index);
    ui->cboxStyle->setCurrentIndex(style);
    on_btnQuery_clicked();
}
