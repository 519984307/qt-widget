#ifndef FRMWEATHER_H
#define FRMWEATHER_H

#include <QWidget>
#include "weather.h"

namespace Ui {
class frmWeather;
}

class frmWeather : public QWidget
{
    Q_OBJECT

public:
    explicit frmWeather(QWidget *parent = 0);
    ~frmWeather();

private:
    Ui::frmWeather *ui;
    QFont iconFont;
    Weather *weather;

private slots:
    void initForm();
    void initTable();
    void initConfig();
    void saveConfig();

private slots:
    //打印信息信号
    void debug(const QString &msg);
    //失败错误信号
    void error(const QString &msg);
    //返回天气信息集合
    void receiveWeather(const QString &city, const QString &wendu, const QString &ganmao, const QList<WeatherInfo> &weatherInfos);

private slots:
    void on_btnQuery_clicked();
    void on_btnLocation_clicked();
    void on_cboxProvince_currentIndexChanged(int);
    void on_cboxCity_currentIndexChanged(int);
    void on_cboxCounty_currentIndexChanged(int);    

public slots:
    void setConfig(const QString &city, int interval, int style);

signals:
    void configChanged(const QString &city, int interval, int style);
};

#endif // FRMWEATHER_H
