#pragma execution_character_set("utf-8")

#include "frmwavedata.h"
#include "ui_frmwavedata.h"
#include "qfile.h"

frmWaveData::frmWaveData(QWidget *parent) : QWidget(parent), ui(new Ui::frmWaveData)
{
    ui->setupUi(this);
    this->initForm();
}

frmWaveData::~frmWaveData()
{
    delete ui;
}

void frmWaveData::initForm()
{
    ui->waveData2->setDataColor(QColor(34, 163, 169));
    ui->waveData3->setDataColor(QColor(162, 121, 197));

    //从资源文件中读取数据
    QString file1 = ":/data/data1.txt";
    QString file2 = ":/data/data2.txt";
    QString file3 = ":/data/data3.txt";
    QVector<float> data1 = readFile(file1);
    QVector<float> data2 = readFile(file2);
    QVector<float> data3 = readFile(file3);

#if 0
    //3条数据显示在同一个控件上
    ui->waveData1->setData(data1);
    ui->waveData1->setData2(data2);
    ui->waveData1->setData3(data3);
#else
    //3条数据显示在不同的控件上
    ui->waveData1->setData(data1);
    ui->waveData2->setData(data2);
    ui->waveData3->setData(data3);
#endif
}

QVector<float> frmWaveData::readFile(const QString &file)
{
    QVector<float> data;
    QFile f(file);
    if (f.open(QFile::ReadOnly)) {
        QString str = f.readAll();
        QStringList list = str.split(" ");
        foreach (QString s, list) {
            data.append(s.toDouble());
        }
    }

    return data;
}
