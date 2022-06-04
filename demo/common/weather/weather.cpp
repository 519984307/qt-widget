#pragma execution_character_set("utf-8")

#include "weather.h"
#include "qfontdatabase.h"
#include "qnetworkaccessmanager.h"
#include "qnetworkreply.h"
#include "qtimer.h"
#include "qdatetime.h"
#include "qeventloop.h"
#include "qlocale.h"
#include "qmutex.h"
#include "qdebug.h"

QFont Weather::getIconFont()
{
    static QFont iconFont;
    QString fontName = "pe-icon-set-weather";
    QString fontFile = ":/font/pe-icon-set-weather.ttf";

    //已经找到天气图形字体
    if (iconFont.family() == "pe-icon-set-weather") {
        return iconFont;
    }

    //判断图形字体是否存在,不存在则加入
    QFontDatabase fontDb;
    if (!fontDb.families().contains(fontName)) {
        int fontId = fontDb.addApplicationFont(fontFile);
        QStringList listName = fontDb.applicationFontFamilies(fontId);
        if (listName.count() == 0) {
            qDebug() << QString("load %1 error").arg(fontName);
        }
    }

    //再次判断是否包含字体名称防止加载失败
    if (fontDb.families().contains(fontName)) {
        iconFont = QFont(fontName);
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,0))
        iconFont.setHintingPreference(QFont::PreferNoHinting);
#endif
    }

    return iconFont;
}

int Weather::getWeatherIcon(const QString &type)
{
    //没有的或者不正确不贴切的自行对照表找到进行修改
    int icon = 0xe999;
    if (type == "晴") {
        icon = 0xe999;
    } else if (type == "多云") {
        icon = 0xe972;
    } else if (type == "阴") {
        icon = 0xe970;
    } else if (type == "阵雨") {
        icon = 0xe97c;
    } else if (type == "雷阵雨") {
        icon = 0xe9b3;
    } else if (type == "雷阵雨伴有冰雹") {
        icon = 0xe935;
    } else if (type == "雨夹雪") {
        icon = 0xe97a;
    } else if (type == "蒙蒙细雨") {
        icon = 0xe915;
    } else if (type == "小雨") {
        icon = 0xe917;
    } else if (type == "中雨") {
        icon = 0xe978;
    } else if (type == "大雨") {
        icon = 0xe94d;
    } else if (type == "暴雨") {
        icon = 0xe94f;
    } else if (type == "大暴雨") {
        icon = 0xe94f;
    } else if (type == "特大暴雨") {
        icon = 0xe94f;
    } else if (type == "阵雪") {
        icon = 0xe984;
    } else if (type == "小雪") {
        icon = 0xe986;
    } else if (type == "中雪") {
        icon = 0xe996;
    } else if (type == "大雪") {
        icon = 0xe997;
    } else if (type == "暴雪") {
        icon = 0xe901;
    } else if (type == "薄雾") {
        icon = 0xe956;
    } else if (type == "雾") {
        icon = 0xe927;
    } else if (type == "大雾") {
        icon = 0xe929;
    } else if (type == "冻雨") {
        icon = 0xe917;
    } else if (type == "沙尘暴") {
        icon = 0xe9c4;
    } else if (type == "小雨-中雨") {
        icon = 0xe94b;
    } else if (type == "中雨-大雨") {
        icon = 0xe94b;
    } else if (type == "大雨-暴雨") {
        icon = 0xe94b;
    } else if (type == "暴雨-大暴雨") {
        icon = 0xe94f;
    } else if (type == "大暴雨-特大暴雨") {
        icon = 0xe94f;
    } else if (type.contains("雨")) {
        icon = 0xe978;
    } else if (type.contains("雪")) {
        icon = 0xe996;
    } else if (type.contains("霾")) {
        icon = 0xe929;
    }
    return icon;
}

Weather::Weather(QObject *parent) : QObject(parent)
{
    //网络请求对象
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(finished(QNetworkReply *)));

    city = "上海";
    label = 0;
    style = 0;

    //定时器查询天气
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(query()));
    timer->setInterval(60 * 1000);

    //主动获取一次图形字体
    getIconFont();
}

QString Weather::replace1(QString text)
{
    text.replace("<![CDATA[", "");
    text.replace("]]>", "");
    return text;
}

QString Weather::replace2(QString text)
{
    text.replace("低温 ", "");
    text.replace("高温 ", "");
    return text;
}

#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
void Weather::getData(QJsonObject objData, QString &city, QString &ganmao, QString &wendu)
{
    city = objData.value("city").toString();
    ganmao = objData.value("ganmao").toString();
    wendu = objData.value("wendu").toString();
}

void Weather::getData(QJsonObject object, WeatherInfo &weatherInfo, bool yesterday)
{
    weatherInfo.date = object.value("date").toString();
    weatherInfo.low = object.value("low").toString();
    weatherInfo.high = object.value("high").toString();
    weatherInfo.type = object.value("type").toString();
    if (yesterday) {
        weatherInfo.fengli = object.value("fl").toString();
        weatherInfo.fengxiang = object.value("fx").toString();
    } else {
        weatherInfo.fengli = object.value("fengli").toString();
        weatherInfo.fengxiang = object.value("fengxiang").toString();
    }

    weatherInfo.low = replace2(weatherInfo.low);
    weatherInfo.high = replace2(weatherInfo.high);
    weatherInfo.fengli = replace1(weatherInfo.fengli);
}

#else
void Weather::getData(QScriptValue objData, QString &city, QString &ganmao, QString &wendu)
{
    city = objData.property("city").toString();
    ganmao = objData.property("ganmao").toString();
    wendu = objData.property("wendu").toString();
}

void Weather::getData(QScriptValue object, WeatherInfo &weatherInfo, bool yesterday)
{
    weatherInfo.date = object.property("date").toString();
    weatherInfo.low = object.property("low").toString();
    weatherInfo.high = object.property("high").toString();
    weatherInfo.type = object.property("type").toString();
    if (yesterday) {
        weatherInfo.fengli = object.property("fl").toString();
        weatherInfo.fengxiang = object.property("fx").toString();
    } else {
        weatherInfo.fengli = object.property("fengli").toString();
        weatherInfo.fengxiang = object.property("fengxiang").toString();
    }

    weatherInfo.low = replace2(weatherInfo.low);
    weatherInfo.high = replace2(weatherInfo.high);
    weatherInfo.fengli = replace1(weatherInfo.fengli);
}
#endif

void Weather::finished(QNetworkReply *reply)
{
    //请求失败则发出错误信号
#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    if (reply->error() != QNetworkReply::NoError && reply->error() != QNetworkReply::InternalServerError) {
#else
    if (reply->error() != QNetworkReply::NoError) {
#endif
        emit error(reply->errorString());
    }

    //{
    //  "data":
    //  {
    //    "yesterday":
    //      {"date":"17日星期六","high":"高温 32℃","fx":"北风","low":"低温 19℃","fl":"<![CDATA[3-4级]]>","type":"晴"},
    //    "city":"北京",
    //    "forecast":[
    //      {"date":"18日星期天","high":"高温 32℃","fengli":"<![CDATA[<3级]]>","low":"低温 21℃","fengxiang":"北风","type":"晴"},
    //      {"date":"19日星期一","high":"高温 31℃","fengli":"<![CDATA[<3级]]>","low":"低温 22℃","fengxiang":"南风","type":"多云"},
    //      {"date":"20日星期二","high":"高温 25℃","fengli":"<![CDATA[<3级]]>","low":"低温 20℃","fengxiang":"南风","type":"小雨"},
    //      {"date":"21日星期三","high":"高温 31℃","fengli":"<![CDATA[<3级]]>","low":"低温 21℃","fengxiang":"北风","type":"多云"},
    //      {"date":"22日星期四","high":"高温 30℃","fengli":"<![CDATA[<3级]]>","low":"低温 22℃","fengxiang":"北风","type":"晴"}
    //    ],
    //    "ganmao":"各项气象条件适宜，发生感冒机率较低。但请避免长期处于空调房间中，以防感冒。",
    //    "wendu":"24"
    //  },
    //  "status":1000,
    //  "desc":"OK"
    //}

    QByteArray buffer = reply->readAll();
    reply->deleteLater();
    QString msg = QString(buffer);
    emit debug(msg);

    //过滤字符
    if (!msg.contains("data") || !msg.contains("yesterday") || !msg.contains("forecast")) {
        return;
    }

    //定义变量存储城市、提示、温度
    QString city, ganmao, wendu;
    //将每天天气信息存入队列
    QList<WeatherInfo> weatherInfos;

    //解析数据
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    //采用qt内置的json方法解析
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(buffer, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        emit error(QString("未知数据( %1 )").arg(msg));
        return;
    }

    QJsonObject objRoot = jsonDoc.object();
    //qDebug() << objRoot.keys();
    QJsonValue data = objRoot.value("data");
    if (!data.isObject()) {
        return;
    }

    //解析城市、感冒、温度
    QJsonObject objData = data.toObject();
    getData(objData, city, ganmao, wendu);

    //解析昨天的天气
    QJsonObject object = objData.value("yesterday").toObject();
    WeatherInfo weatherInfo;
    getData(object, weatherInfo, true);
    weatherInfos << weatherInfo;

    //解析今天及未来几天的天气
    QJsonValue value = objData.value("forecast");
    if (value.isArray()) {
        QJsonArray array = value.toArray();
        for (int i = 0; i < array.count(); i++) {
            QJsonObject object = array.at(i).toObject();
            WeatherInfo weatherInfo;
            getData(object, weatherInfo, false);
            weatherInfos << weatherInfo;
        }
    }
#else
    //初始化脚本引擎
    QScriptEngine engine;
    //构建解析对象
    QScriptValue script = engine.evaluate("value=" + buffer);
    if (!script.isObject()) {
        emit error(QString("未知数据( %1 )").arg(msg));
        return;
    }

    //取出数据结果数组
    QScriptValue data = script.property("data");
    if (!data.isObject()) {
        return;
    }

    //解析城市、感冒、温度
    QScriptValue objData = data.toObject();
    getData(objData, city, ganmao, wendu);

    //解析昨天的天气
    QScriptValue object = objData.property("yesterday").toObject();
    WeatherInfo weatherInfo;
    getData(object, weatherInfo, true);
    weatherInfos << weatherInfo;

    //解析今天及未来几天的天气
    QScriptValue value = objData.property("forecast");
    if (!value.isArray()) {
        return;
    }

    //创建迭代器逐个解析具体值
    QScriptValueIterator it(value);
    while (it.hasNext()) {
        it.next();
        if (it.flags() & QScriptValue::SkipInEnumeration) {
            continue;
        }

        QScriptValue object = it.value();
        WeatherInfo weatherInfo;
        getData(object, weatherInfo, false);
        weatherInfos << weatherInfo;
    }
#endif

    //补全摄氏度
    wendu = wendu + "℃";
    //处理天气标签
    doWeather(city, wendu, ganmao, weatherInfos);
    //发出信号通知
    emit receiveWeather(city, wendu, ganmao, weatherInfos);
}

void Weather::doWeather(const QString &city, const QString &wendu, const QString &ganmao, const QList<WeatherInfo> &weatherInfos)
{
    //取出今天的天气情况设置到标签
    if (label != 0 && weatherInfos.count() > 1) {
        WeatherInfo weatherInfo = weatherInfos.at(1);
        QString text;
        if (style == 1) {
            text = QString("温度: %1  |  天气: %2  |  风力: %3  |  风向: %4")
                   .arg(wendu).arg(weatherInfo.type).arg(weatherInfo.fengli).arg(weatherInfo.fengxiang);
        } else if (style == 2) {
            text = QString("温度: %1 | 天气: %2 | 风力: %3 - %4")
                   .arg(wendu).arg(weatherInfo.type).arg(weatherInfo.fengli).arg(weatherInfo.fengxiang);
        } else if (style == 3) {
            text = QString("当前: %1 | 温度: %2 - %3 | 天气: %4  ")
                   .arg(wendu).arg(weatherInfo.low).arg(weatherInfo.high).arg(weatherInfo.type);
        } else if (style == 4) {
            //html表格格式
            QStringList list;
            list << "<table border='0.0' cellspacing='0' cellpadding='2' style='vertical-align:middle;text-align:center;'>";
            //占多行图形字体通用样式 左右设置点边距看起来更舒服
            QString style = "rowspan='2' style='font-size:40px;font-family:pe-icon-set-weather;padding:0px 10px 0px 10px;'";

            //获取日期周几,在Qt6中默认英文需要转换 星期二=Tuesday
            //ddd = 周二 Tue  dddd = 星期二 Tuesday
            QLocale local = QLocale::Chinese;
            QDateTime today = QDateTime::currentDateTime();
            WeatherInfo weatherInfo1 = weatherInfos.at(1);
            WeatherInfo weatherInfo2 = weatherInfos.at(2);
            WeatherInfo weatherInfo3 = weatherInfos.at(3);

            list << "<tr>";
            list << QString("<td %1>%2</td>").arg(style).arg((QChar)getWeatherIcon(weatherInfo1.type));
            list << QString("<td>今天（%1）</td>").arg(local.toString(today, "ddd"));
            list << QString("<td %1>%2</td>").arg(style).arg((QChar)getWeatherIcon(weatherInfo2.type));
            list << QString("<td>明天（%1）</td>").arg(local.toString(today.addDays(1), "ddd"));
            list << QString("<td %1>%2</td>").arg(style).arg((QChar)getWeatherIcon(weatherInfo3.type));
            list << QString("<td>后天（%1）</td>").arg(local.toString(today.addDays(2), "ddd"));
            list << "</tr>";

            list << "<tr>";
            list << QString("<td>%1 - %2</td>").arg(replace2(weatherInfo1.low)).arg(replace2(weatherInfo1.high));
            list << QString("<td>%1 - %2</td>").arg(replace2(weatherInfo2.low)).arg(replace2(weatherInfo2.high));
            list << QString("<td>%1 - %2</td>").arg(replace2(weatherInfo3.low)).arg(replace2(weatherInfo3.high));
            list << "</tr>";

            list << "<tr>";
            QString td = QString("<td style='text-align:center;'>%1</td>").arg(city);
            list << td;
            list << QString("<td>%1 %2</td>").arg(weatherInfo1.type).arg(weatherInfo1.fengxiang);
            list << td;
            list << QString("<td>%1 %2</td>").arg(weatherInfo2.type).arg(weatherInfo2.fengxiang);
            list << td;
            list << QString("<td>%1 %2</td>").arg(weatherInfo3.type).arg(weatherInfo3.fengxiang);
            list << "</tr>";

            list << "</table>";
            text = list.join("");
        }

        label->setText(text);
    }
}

void Weather::query(const QString &city)
{
    if (city.isEmpty()) {
        return;
    }

    QString url = QString("http://wthrcdn.etouch.cn/weather_mini?city=%1").arg(city);
    QNetworkRequest quest;
    quest.setUrl(QUrl(url));
    manager->get(quest);
}

void Weather::query()
{
    query(this->city);
}

void Weather::setCity(const QString &city)
{
    this->city = city;
}

void Weather::setLabel(QLabel *label, quint8 style)
{
    this->label = label;
    this->style = style;
    if (style == 0) {
        label->setText("");
    }
}

void Weather::start(int interval)
{
    //采集间隔0表示不采集
    if (label == 0 || interval <= 0) {
        return;
    }

    //启动定时器轮询天气
    this->stop();
    timer->start(interval * 1000);
}

void Weather::stop()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

QString Weather::getLocation()
{
    int timeout = 3000;
    QString url = "https://pv.sohu.com/cityjson?ie=utf-8";

    //初始化网络请求对象
    QNetworkAccessManager manager;
    //局部的事件循环,不卡主界面
    QEventLoop eventLoop;

    //设置超时 5.15开始自带了超时时间函数 默认30秒
#if (QT_VERSION >= QT_VERSION_CHECK(5,15,0))
    manager.setTransferTimeout(timeout);
#else
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    timer.setSingleShot(true);
    timer.start(timeout);
#endif

    //启动网络请求
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    //读取结果
    QByteArray data = reply->readAll();
    reply->deleteLater();
    return data;
}
