#pragma execution_character_set("utf-8")

#include "frmexamplessimple.h"
#include "ui_frmexamplessimple.h"
#include "qpainter.h"

#include "../../demo/gauge/gaugecar/frmgaugecar.h"
#include "../../demo/gauge/gaugecloud/frmgaugecloud.h"
#include "../../demo/gauge/gaugecolor/frmgaugecolor.h"
#include "../../demo/gauge/gaugecompass/frmgaugecompass.h"
#include "../../demo/gauge/gaugecompasspan/frmgaugecompasspan.h"
#include "../../demo/gauge/gaugedial/frmgaugedial.h"
#include "../../demo/gauge/gaugemini/frmgaugemini.h"
#include "../../demo/gauge/gaugepanel/frmgaugepanel.h"
#include "../../demo/gauge/gaugeprogress/frmgaugeprogress.h"
#include "../../demo/gauge/gaugespeed/frmgaugespeed.h"

#include "../../demo/progress/progressbutton/frmprogressbutton.h"
#include "../../demo/progress/progresspercent/frmprogresspercent.h"
#include "../../demo/progress/progressring/frmprogressring.h"
#include "../../demo/progress/progressshadow/frmprogressshadow.h"
#include "../../demo/progress/progresstip/frmprogresstip.h"

#include "../../demo/painter/battery/frmbattery.h"
#include "../../demo/painter/lightbutton/frmlightbutton.h"
#include "../../demo/painter/lunarcalendarwidget/frmlunarcalendarwidget.h"
#include "../../demo/painter/magicpoolfish/frmmagicpoolfish.h"
#include "../../demo/painter/telwidget/frmtelwidget.h"

#include "../../demo/custom/customring/frmcustomring.h"
#include "../../demo/custom/customgraphics/frmcustomgraphics.h"
#include "../../demo/custom/shadowcalendar/frmshadowcalendar.h"
#include "../../demo/custom/spiderchart/frmspiderchart.h"
#include "../../demo/custom/timeaxis/frmtimeaxis.h"
#include "../../demo/custom/customdart/frmcustomdart.h"
#include "../../demo/custom/tasktableview/frmtasktableview.h"

#include "../../demo/ruler/rulerprogress/frmrulerprogress.h"
#include "../../demo/color/colorpanel/frmcolorpanel.h"
#include "../../demo/image/adswidget2/frmadswidget2.h"
#include "../../demo/image/imageclock/frmimageclock.h"
#include "../../demo/other/selectwidget/frmselectwidget.h"
#include "../../demo/wave/wavewater/frmwavewater.h"
#include "../../demo/slider/sliderselect/frmsliderselect.h"
#include "../../demo/flight/frmflightall.h"

frmExamplesSimple::frmExamplesSimple(QWidget *parent) : QWidget(parent), ui(new Ui::frmExamplesSimple)
{
    ui->setupUi(this);
    this->initForm();
    this->addItem();
}

frmExamplesSimple::~frmExamplesSimple()
{
    delete ui;
}

void frmExamplesSimple::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawTiledPixmap(rect(), bgPix);
}

void frmExamplesSimple::initForm()
{
    bgPix = QPixmap(":/image/bg.png");
    connect(ui->navListView, SIGNAL(pressed(QString, QString)), this, SLOT(pressed(QString, QString)));

    //设置文本边距
    ui->navListView->setChildMargin(28);
    ui->navListView->setFixedWidth(190);
    ui->navListView->setExpendMode(NavListView::ExpendMode_SingleClick);
    ui->navListView->setSeparateColor(QColor(40, 43, 51));

    //设置子节点颜色
    ui->navListView->setChildBgNormalColor(QColor(40, 43, 51));
    ui->navListView->setChildBgSelectedColor(QColor(20, 20, 20));
    ui->navListView->setChildBgHoverColor(QColor(20, 20, 20));
    ui->navListView->setChildTextNormalColor(QColor(180, 180, 180));
    ui->navListView->setChildTextSelectedColor(QColor(250, 250, 250));
    ui->navListView->setChildTextHoverColor(QColor(255, 255, 255));

    //设置父节点颜色
    ui->navListView->setParentBgNormalColor(QColor(57, 61, 73));
    ui->navListView->setParentBgSelectedColor(QColor(78, 83, 102));
    ui->navListView->setParentBgHoverColor(QColor(78, 83, 102));
    ui->navListView->setParentTextNormalColor(QColor(250, 250, 250));
    ui->navListView->setParentTextSelectedColor(QColor(250, 250, 250));
    ui->navListView->setParentTextHoverColor(QColor(250, 250, 250));
}

void frmExamplesSimple::addItem()
{
    ui->stackedWidget->addWidget(new frmGaugeCar);
    ui->stackedWidget->addWidget(new frmGaugeCloud);
    ui->stackedWidget->addWidget(new frmGaugeColor);
    ui->stackedWidget->addWidget(new frmGaugeCompass);
    ui->stackedWidget->addWidget(new frmGaugeCompassPan);
    ui->stackedWidget->addWidget(new frmGaugeDial);
    ui->stackedWidget->addWidget(new frmGaugeMini);
    ui->stackedWidget->addWidget(new frmGaugePanel);
    ui->stackedWidget->addWidget(new frmGaugeProgress);
    ui->stackedWidget->addWidget(new frmGaugeSpeed);

    ui->stackedWidget->addWidget(new frmProgressButton);
    ui->stackedWidget->addWidget(new frmProgressPercent);
    ui->stackedWidget->addWidget(new frmProgressRing);
    ui->stackedWidget->addWidget(new frmProgressShadow);
    ui->stackedWidget->addWidget(new frmProgressTip);

    ui->stackedWidget->addWidget(new frmBattery);
    ui->stackedWidget->addWidget(new frmLightButton);
    ui->stackedWidget->addWidget(new frmLunarCalendarWidget);
    ui->stackedWidget->addWidget(new frmMagicPoolFish);
    ui->stackedWidget->addWidget(new frmTelWidget);

    ui->stackedWidget->addWidget(new frmCustomRing);
    ui->stackedWidget->addWidget(new frmCustomGraphics);
    ui->stackedWidget->addWidget(new frmShadowCalendar);
    ui->stackedWidget->addWidget(new frmSpiderChart);
    ui->stackedWidget->addWidget(new frmTimeAxis);
    ui->stackedWidget->addWidget(new frmCustomDart);
    ui->stackedWidget->addWidget(new frmTaskTableView);

    ui->stackedWidget->addWidget(new frmRulerProgress);
    ui->stackedWidget->addWidget(new frmColorPanel);
    ui->stackedWidget->addWidget(new frmAdsWidget2);
    ui->stackedWidget->addWidget(new frmImageClock);
    ui->stackedWidget->addWidget(new frmSelectWidget);
    ui->stackedWidget->addWidget(new frmWaveWater);
    ui->stackedWidget->addWidget(new frmSliderSelect);

    ui->stackedWidget->addWidget(new frmFlightAll);

    listName << "汽车仪表盘" << "云台仪表盘" << "多彩仪表盘" << "指南针表盘" << "指南针面板"
             << "旋转仪表盘" << "迷你仪表盘" << "面板仪表盘" << "进度仪表盘" << "速度仪表盘";

    listName << "按钮进度条" << "百分比进度" << "环形进度条" << "光晕进度条" << "提示进度条";

    listName << "电池电量" << "高亮按钮" << "农历控件" << "游动的鱼" << "手机通讯录";

    listName << "环形图表" << "多边形状" << "光晕日历" << "蜘蛛网图" << "垂直时间轴"
             << "自定义飞镖盘" << "任务策略表格";

    listName << "进度标尺" << "颜色面板" << "图片轮播" << "图片时钟" << "描点跟随"
             << "水波效果" << "范围选择条" << "飞控套件";

    addItem("精美控件", listName);

    QString item = listItem.join(",");
    ui->navListView->setItems(item);

    this->setWindowTitle("Qt自定义控件大全 V2022 (QQ: 517216493 WX: feiyangqingyun)");
    ui->navListView->setCurrentRow(0);
}

void frmExamplesSimple::addItem(const QString &parentName, const QStringList &childNames)
{
    //设置节点数据格式: 标题|父节点标题(父节点为空)|是否展开(0展开)|提示信息|左侧图标
    int count = childNames.count();
    listItem << QString("%1||0|%2|").arg(parentName).arg(count);
    for (int i = 0; i < count; i++) {
        listItem << QString("%1. %2|%3|1||0xf0da").arg(i + 1, 2, 10, QChar('0')).arg(childNames.at(i)).arg(parentName);
    }
}

void frmExamplesSimple::pressed(const QString &childText, const QString &parentText)
{
    //如果带了 . 表示序号,要删除再比较
    QString text = childText;
    if (text.contains(".")) {
        text = text.mid(text.indexOf(".") + 2, text.length());
    }

    int index = listName.indexOf(text);
    if (index >= 0) {
        ui->stackedWidget->setCurrentIndex(index);
    }
}
