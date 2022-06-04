#pragma execution_character_set("utf-8")

#include "frmtimeaxis.h"
#include "ui_frmtimeaxis.h"
#include "qscrollbar.h"
#include "qdatetime.h"
#include "timeaxis.h"

frmTimeAxis::frmTimeAxis(QWidget *parent) : QWidget(parent), ui(new Ui::frmTimeAxis)
{
    ui->setupUi(this);
    this->initForm();
}

frmTimeAxis::~frmTimeAxis()
{

}

void frmTimeAxis::initForm()
{
    ui->timeAxis->verticalScrollBar()->hide();
    ui->timeAxis->setTitle("公司发展历程");

    //有两种方式设置信息集合
#if 1
    QStringList list;
    list << "2010.07,公司成立" << "2010.08,研发部成立" << "2011.5,产品发布上线";
    list << "2012.02,成立上海研发中心" << "2012.12,年营业额突破1亿" << "2013.6,重量级核心产品问世";
    list << "2014.11,成立各级分销中心" << "2015.03,总营业额突破10亿" << "2017.5,公司上市";
    ui->timeAxis->setInfos(list.join("|"));
#else
    QDateTime now = QDateTime::currentDateTime();
    QList<TimeAxisWidget::TimeAxisInfo> itemInfos;
    for (int i = 1; i <= 10; i++) {
        TimeAxisWidget::TimeAxisInfo itemInfo;
        QDateTime date = now.addMonths(i);
        itemInfo.time = date.toString("yyyy.MM.dd");
        itemInfo.info = QString("公司营业额突破%1亿").arg(i);
        itemInfos << itemInfo;
    }
    ui->timeAxis->getWidget()->setItemInfos(itemInfos);
#endif

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QColor("#333645"));
    this->setPalette(palette);
    this->setAutoFillBackground(true);
}
