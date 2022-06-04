#pragma execution_character_set("utf-8")

#include "frmspiderchart.h"
#include "ui_frmspiderchart.h"
#include "qdebug.h"

frmSpiderChart::frmSpiderChart(QWidget *parent) : QWidget(parent), ui(new Ui::frmSpiderChart)
{
    ui->setupUi(this);
    this->initForm();
}

frmSpiderChart::~frmSpiderChart()
{
    delete ui;
}

void frmSpiderChart::initForm()
{
    //设置边对应的文字描述
    //QString text = "1|2|3|4|5|6|7";
    QString text = "语文|数学|英语|物理|化学|历史|地理";
    ui->spiderChart->setSideText(text);

    //添加数据
    QVector<float> data1;
    data1 << 30 << 80 << 50 << 65 << 70 << 63 << 88;
    ui->spiderChart->addData("张三", data1, QColor(84, 111, 198));

    QVector<float> data2;
    data2 << 35 << 70 << 74 << 66 << 90 << 98 << 65;
    ui->spiderChart->addData("李四", data2, QColor(155, 96, 180));
}

void frmSpiderChart::on_btnAdd_clicked()
{
    QVector<float> data;
    int count = ui->sboxSideCount->value();
    QString name = ui->txtSideName->text().trimmed();
    for (int i = 0; i < count; ++i) {
        data << rand() % 100;
    }

    //随机颜色
    QColor color = QColor(rand() % 255, rand() % 255, rand() % 255);
    ui->spiderChart->addData(name, data, color);

    //自动更新名称
    if (name.startsWith("系列")) {
        int index = name.mid(2, 10).toInt() + 1;
        name = QString("系列%1").arg(index);
    }
    ui->txtSideName->setText(name);
}

void frmSpiderChart::on_sboxLevelCount_valueChanged(int arg1)
{
    ui->spiderChart->setLevelCount(arg1);
}

void frmSpiderChart::on_sboxSideCount_valueChanged(int arg1)
{
    //边数的改变可能导致里边数据点的绘制发生变化因为有些数据没有按照边数来设置
    ui->spiderChart->setSideCount(arg1);

    //设置边对应的文字描述
    QStringList list;
    for (int i = 0; i < arg1; ++i) {
        list << QString::number(i + 1);
    }
    ui->spiderChart->setSideText(list.join("|"));
}

