#pragma execution_character_set("utf-8")

#include "cityhelper.h"
#include "qfile.h"
#include "qfileinfo.h"
#include "qdir.h"
#include "qtextstream.h"
#include "qdatetime.h"
#include "qdebug.h"

#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qjsonvalue.h"
#endif

QString CityHelper::getValue(const QString &value)
{
    QString result = value.trimmed();
    result = result.replace("\"", "");
    result = result.replace(",", "");
    result = result.split(":").last().trimmed();
    return result;
}

QByteArray CityHelper::getFile(const QString &jsonFile)
{
    //读取数据,已知jsonFile是固定的所以这里缓存下,如果是同一个文件则不用继续读取
    static QString fileName;
    static QByteArray data;
    if (fileName != jsonFile) {
        fileName = jsonFile;
        QFile fileJson(jsonFile);
        if (fileJson.open(QFile::ReadOnly | QFile::Text)) {
            data = fileJson.readAll();
            fileJson.close();
        }
    }

    return data;
}

QStringList CityHelper::getResult(const QByteArray &data, quint8 type, const QString &provinceName, const QString &cityName)
{
    //处理数据
    QStringList result;
    if (type == 1 && provinceName.isEmpty()) {
        return result;
    } else if (type == 2 && (provinceName.isEmpty() || cityName.isEmpty())) {
        return result;
    }

#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    //采用qt内置的json方法解析
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError) {
        return result;
    }

    QJsonObject rootObj = jsonDoc.object();
    //qDebug() << rootObj.keys();
    if (!rootObj.contains("province")) {
        return result;
    }

    QJsonArray province = rootObj.value("province").toArray();
    for (int i = 0; i < province.count(); i++) {
        QJsonObject subObj = province.at(i).toObject();
        if (!subObj.contains("name")) {
            continue;
        }

        QString name = subObj.value("name").toString();
        if (type == 0) {
            result << name;
        } else if (type == 1) {
            if (name != provinceName) {
                continue;
            }

            QJsonArray city = subObj.value("city").toArray();
            for (int j = 0; j < city.count(); j++) {
                QJsonObject nodeObj = city.at(j).toObject();
                if (nodeObj.contains("cityname")) {
                    QString cityname = nodeObj.value("cityname").toString();
                    result << cityname;
                }
            }

            //退出查找
            break;
        } else if (type == 2) {
            if (name != provinceName) {
                continue;
            }

            bool exist = false;
            QJsonArray city = subObj.value("city").toArray();
            for (int j = 0; j < city.count(); j++) {
                QJsonObject nodeObj = city.at(j).toObject();
                if (!nodeObj.contains("cityname")) {
                    continue;
                }

                QString cityname = nodeObj.value("cityname").toString();
                if (cityname != cityName) {
                    continue;
                }

                QJsonArray countyname = nodeObj.value("countyname").toArray();
                for (int k = 0; k < countyname.count(); k++) {
                    QString county = countyname.at(k).toString();
                    //数据中带了县城所在镇,要过滤
                    if (!county.endsWith("镇")) {
                        result << county;
                    }
                }
                exist = true;
                break;
            }

            //退出最外层查找
            if (exist) {
                break;
            }
        }
    }
#else
    //采用字符串分割方法解析
    QString temp = data;
    QStringList provice = temp.split("\n");
    QString name, cityname;
    for (int i = 0; i < provice.count(); i++) {
        QString value = provice.at(i);
        if (value.contains("\"name\"")) {
            name = getValue(value);
            if (type == 0) {
                result << name;
            }
        } else if (value.contains("\"cityname\"")) {
            cityname = getValue(value);
            bool exist = false;
            if (name == provinceName) {
                exist = true;
            }

            if (type != 1) {
                continue;
            }

            //检测到是当前省份则来提取市区
            if (exist) {
                result << cityname;
                //当是新的省份以后立即退出
                if (name != provinceName) {
                    break;
                }
            }
        } else if (value.contains("\"countyname\"")) {
            if (type != 2) {
                continue;
            }

            if (name != provinceName || cityname != cityName) {
                continue;
            }

            QString county = getValue(value);
            county = county.mid(1, county.length() - 2);
            QStringList countys = county.split(" ");
            foreach (QString county, countys) {
                //数据中带了县城所在镇,要过滤
                if (!county.endsWith("镇")) {
                    result << county;
                }
            }
            break;
        }
    }
#endif
    return result;
}

QStringList CityHelper::getProvince(const QString &jsonFile)
{
    QByteArray data = getFile(jsonFile);
    return getResult(data, 0, "", "");
}

QStringList CityHelper::getCity(const QString &jsonFile, const QString &provinceName)
{
    QByteArray data = getFile(jsonFile);
    return getResult(data, 1, provinceName, "");
}

QStringList CityHelper::getCounty(const QString &jsonFile, const QString &provinceName, const QString &cityName)
{
    QByteArray data = getFile(jsonFile);
    return getResult(data, 2, provinceName, cityName);
}
