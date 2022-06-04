#include "frmiptool.h"
#include "ui_frmiptool.h"
#include <QtNetwork>
#include <QRegExp>

frmIPTool::frmIPTool(QWidget *parent) :	QWidget(parent), ui(new Ui::frmIPTool)
{
    ui->setupUi(this);
}

frmIPTool::~frmIPTool()
{
    delete ui;
}

//判断IP地址及端口是否在线
bool frmIPTool::ipLive(const QString &ip, int port)
{
    QTcpSocket tcpClient;
    tcpClient.abort();
    tcpClient.connectToHost(ip, port);
    //100毫秒没有连接上则判断不在线
    return tcpClient.waitForConnected(100);
}

//获取网页所有源代码
QString frmIPTool::getHtml(const QString &url)
{
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop eventLoop;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    QByteArray data = reply->readAll();
    reply->deleteLater();
    return QString(data);
}

//获取本机公网IP地址
QString frmIPTool::getNetIP(const QString &html)
{
    QString ip;
    QStringList list = html.split(" ");
    foreach (QString str, list) {
        //value=\"101.86.197.178\">
        if (str.contains("value=")) {
            QStringList temp = str.split("\"");
            ip = temp.at(1);
            break;
        }
    }
    return ip;
}

//获取本机IP
QString frmIPTool::getLocalIP()
{
    //优先取192开头的IP,如果获取不到IP则取127.0.0.1
    QString ip = "127.0.0.1";
    QStringList ips = getLocalIPs();
    foreach (QString str, ips) {
        if (str.startsWith("192.168.1") || str.startsWith("192")) {
            ip = str;
            break;
        }
    }

    return ip;
}

QStringList frmIPTool::getLocalIPs()
{
    static QStringList ips;
    if (ips.count() == 0) {
#ifndef Q_OS_WASM
        QList<QNetworkInterface> netInterfaces = QNetworkInterface::allInterfaces();
        foreach (const QNetworkInterface  &netInterface, netInterfaces) {
            //移除虚拟机和抓包工具的虚拟网卡
            QString humanReadableName = netInterface.humanReadableName().toLower();
            if (humanReadableName.startsWith("vmware network adapter") || humanReadableName.startsWith("npcap loopback adapter")) {
                continue;
            }

            //过滤当前网络接口
            bool flag = (netInterface.flags() == (QNetworkInterface::IsUp | QNetworkInterface::IsRunning | QNetworkInterface::CanBroadcast | QNetworkInterface::CanMulticast));
            if (flag) {
                QList<QNetworkAddressEntry> addrs = netInterface.addressEntries();
                foreach (QNetworkAddressEntry addr, addrs) {
                    //只取出IPV4的地址
                    if (addr.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                        QString ip4 = addr.ip().toString();
                        if (ip4 != "127.0.0.1") {
                            ips.append(ip4);
                        }
                    }
                }
            }
        }
#endif
    }

    return ips;
}

//判断是否是IP地址
bool frmIPTool::isIP(const QString &ip)
{
    QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    return RegExp.exactMatch(ip);
}

//判断是否通外网
bool frmIPTool::isWebOk()
{
    //能接通百度IP说明可以通外网
    return ipLive("www.baidu.com", 80);
}

void frmIPTool::on_btnGetLocalIP_clicked()
{
    ui->txtLocalIP->clear();
    ui->txtLocalIP->setText(getLocalIP());
}

void frmIPTool::on_btnGetWebIP_clicked()
{
    ui->txtWebIP->clear();

    if (!isWebOk()) {
        ui->txtWebIP->setText("net error");
        return;
    }

    ui->txtWebIP->setText(getNetIP(getHtml("http://whois.pconline.com.cn/")));
}

void frmIPTool::on_btnWebOk_clicked()
{
    ui->txtWebOk->clear();
    ui->txtWebOk->setText(isWebOk() ? "true" : "false");
}

void frmIPTool::on_btnUrlIP_clicked()
{
    ui->txtIP->clear();

    if (!isWebOk()) {
        ui->txtIP->setText("net error");
        return;
    }

    QString url = ui->txtUrl->text();
    QHostInfo host = QHostInfo::fromName(url);
    ui->txtIP->setText(host.addresses().at(0).toString());
}
