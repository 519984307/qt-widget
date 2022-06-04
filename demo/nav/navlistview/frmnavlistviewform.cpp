#pragma execution_character_set("utf-8")

#include "frmnavlistviewform.h"
#include "ui_frmnavlistviewform.h"
#include "qdebug.h"

frmNavListViewForm::frmNavListViewForm(QWidget *parent) : QWidget(parent), ui(new Ui::frmNavListViewForm)
{
    ui->setupUi(this);
    this->initForm();
}

frmNavListViewForm::~frmNavListViewForm()
{
    delete ui;
}

void frmNavListViewForm::initForm()
{
    ui->navListView->setSeparateHeight(1);
    ui->navListView->setSeparateColor(QColor(40, 43, 51));

    //设置节点高度相当于间距,可以自行看效果
    //ui->navListView->setParentHeight(50);
    //ui->navListView->setChildHeight(50);
    //设置节点左侧边距,可以自行看效果
    //ui->navListView->setParentMargin(10);
    //ui->navListView->setChildMargin(10);
    //ui->navListView->setParentIconMargin(30);
    //ui->navListView->setChildIconMargin(30);

    ui->navListView->setChildBgNormalColor(QColor(40, 43, 51));
    ui->navListView->setChildBgSelectedColor(QColor(20, 20, 20));
    ui->navListView->setChildBgHoverColor(QColor(20, 20, 20));
    ui->navListView->setChildTextNormalColor(QColor(180, 180, 180));
    ui->navListView->setChildTextSelectedColor(QColor(250, 250, 250));
    ui->navListView->setChildTextHoverColor(QColor(255, 255, 255));

    ui->navListView->setParentBgNormalColor(QColor(57, 61, 73));
    ui->navListView->setParentBgSelectedColor(QColor(78, 83, 102));
    ui->navListView->setParentBgHoverColor(QColor(78, 83, 102));
    ui->navListView->setParentTextNormalColor(QColor(250, 250, 250));
    ui->navListView->setParentTextSelectedColor(QColor(250, 250, 250));
    ui->navListView->setParentTextHoverColor(QColor(250, 250, 250));

    ui->navListView->setExpendMode(NavListView::ExpendMode_SingleClick);

    //设置节点数据格式: 标题|父节点标题(父节点为空)|是否展开(0展开)|提示信息|左侧图标
    QStringList items;
    items.append("主界面||0|正常|");
    items.append("地图监控|主界面|||0xf03e");
    items.append("视频监控|主界面|||0xf03d");
    items.append("设备监控|主界面|||0xf108");

    //支持多种方式设置,下面演示如何改成图片文件
#if 0
    items.append("系统设置||0||:/image/0.png");
    items.append("防区信息|系统设置|||:/image/1.png");
    items.append("位置调整|系统设置|||:/image/2.png");
    items.append("地图编辑|系统设置|||:/image/3.png");
#else
    items.append("系统设置||0||");
    items.append("防区信息|系统设置|||0xf0e8");
    items.append("位置调整|系统设置|||0xf060");
    items.append("地图编辑|系统设置|||0xf03e");
#endif

    items.append("警情查询||0|120|");
    items.append("记录查询|警情查询|||0xf073");
    items.append("图像查询|警情查询|||0xf03e");
    items.append("视频查询|警情查询|||0xf03d");
    items.append("数据回放|警情查询|||0xf080");

    items.append("帮助文档||1|1024|0xf1d7");

    ui->navListView->setItems(items.join(","));
    ui->navListView->setCurrentRow(0);
    on_navListView_pressed(ui->navListView->currentIndex());
}

void frmNavListViewForm::on_navListView_pressed(const QModelIndex &index)
{
    QString text = index.data().toString();
    if (text == "地图监控") {
        ui->stackedWidget->setCurrentIndex(0);
    } else if (text == "视频监控") {
        ui->stackedWidget->setCurrentIndex(1);
    } else if (text == "设备监控") {
        ui->stackedWidget->setCurrentIndex(2);
    }
}
