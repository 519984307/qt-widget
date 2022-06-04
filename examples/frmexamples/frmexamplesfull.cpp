#pragma execution_character_set("utf-8")

#include "frmexamplesfull.h"
#include "ui_frmexamplesfull.h"
#include "qpainter.h"
#include "qdatetime.h"

#include "../frmall/frmgauge.h"
#include "../frmall/frmprogress.h"
#include "../frmall/frmpainter.h"
#include "../frmall/frmcustom.h"
#include "../frmall/frmnav.h"
#include "../frmall/frmwave.h"
#include "../frmall/frmruler.h"
#include "../frmall/frmslider.h"
#include "../frmall/frmbar.h"
#include "../frmall/frmcolor.h"
#include "../frmall/frmimage.h"
#include "../frmall/frmother.h"
#include "../frmall/frmvideo.h"
#include "../frmall/frmflight.h"
#include "../frmall/frmxcontrol.h"
#include "../frmall/frmycontrol.h"
#include "../frmall/frmwidget.h"
#include "../frmall/frmcommon.h"
#include "../frmall/frmtool.h"
#include "../frmall/frmqtdemo.h"

frmExamplesFull::frmExamplesFull(QWidget *parent) : QWidget(parent), ui(new Ui::frmExamplesFull)
{
    ui->setupUi(this);
    this->initForm();
    this->initWidget();
    this->initParent();
    this->initChild();
    this->addItem();
}

frmExamplesFull::~frmExamplesFull()
{
    delete ui;
}

void frmExamplesFull::resizeEvent(QResizeEvent *)
{
    //Qt5.0到Qt5.9之间的版本会执行,一旦缩放超过125%则会在加载后1s内触发两次
    //qDebug() << TIMEMS << this->width() << this->height();
    static bool isResize = false;
    static QDateTime resizeTime = QDateTime::currentDateTime();
    QDateTime now = QDateTime::currentDateTime();
    int offset = resizeTime.msecsTo(now);
    if (!isResize && offset > 0 && offset < 300 && size() != QSize(1050, 650)) {
        isResize = true;
        if (!isMaximized()) {
            this->resize(1050, 650);
        }
    }
}

void frmExamplesFull::closeEvent(QCloseEvent *)
{
    //exit(0);
}

void frmExamplesFull::paintEvent(QPaintEvent *)
{
    if (needDraw) {
        QPainter painter(this);
        painter.drawTiledPixmap(rect(), bgPix);
    }
}

void frmExamplesFull::initForm()
{
    //是否绘制特殊背景
    needDraw = true;
    //需要绘制的控件的名称集合
    listDraw << "仪表盘" << "进度条" << "按钮进度条" << "多态进度条" << "播放进度条" << "环形进度条"
             << "汽车仪表盘" << "半圆仪表盘" << "进度仪表盘" << "时钟仪表盘" << "简单仪表盘" << "钟形仪表盘"
             << "指南针表盘" << "简易指南针" << "指南针面板" << "旋转仪表盘" << "飞机仪表盘" << "多彩仪表盘"
             << "云台仪表盘" << "天气仪表盘" << "分贝仪表盘" << "面板仪表盘" << "可输入表盘" << "时速仪表盘"
             << "圆环仪表盘" << "轨道仪表盘" << "圆弧进度条" << "提示进度条" << "水波进度条"
             << "高亮按钮" << "旋转圆形" << "旋转图形" << "探探雷达" << "魔法小鱼" << "魔法老鼠" << "魔法水滴" << "游动的鱼"
             << "自定义飞镖盘" << "图片背景日历" << "图片背景时钟"
             << "烤箱旋转按钮" << "自定义多边形" << "自定义摇杆" << "自定义饼状图" << "自定义环形图" << "蚂蚁线" << "描点跟随窗体";

    bgPix = QPixmap(":/image/bg.png");
    connect(ui->navListView, SIGNAL(pressed(QString, QString)), this, SLOT(pressed(QString, QString)));

    //设置文本边距
    ui->navListView->setChildMargin(28);
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

void frmExamplesFull::initWidget()
{
    widgets << new frmGauge;
    widgets << new frmProgress;
    widgets << new frmPainter;
    widgets << new frmCustom;
    widgets << new frmNav;
    widgets << new frmWave;
    widgets << new frmRuler;
    widgets << new frmSlider;
    widgets << new frmBar;
    widgets << new frmColor;
    widgets << new frmImage;
    widgets << new frmOther;
    widgets << new frmVideo;
    widgets << new frmFlight;
    widgets << new frmXControl;
    widgets << new frmYControl;
    widgets << new frmWidget;
    widgets << new frmCommon;
    widgets << new frmTool;
    widgets << new frmQtDemo;

    foreach (QWidget *widget, widgets) {
        listChilds << QStringList();
        ui->stackedWidget->addWidget(widget);
    }
}

void frmExamplesFull::initParent()
{
    //一级标题文字集合
#if 0
    ui->navListView->setFixedWidth(200);
    listParent << "表盘控件 - 闭源" << "进度控件 - 闭源" << "基础自绘 - 部开" << "高级自绘 - 闭源"
               << "导航指示 - 闭源" << "波形曲线 - 部开" << "标尺刻度 - 闭源" << "滑动控件 - 闭源"
               << "柱形控件 - 闭源" << "颜色控件 - 闭源" << "贴图控件 - 部开" << "其他控件 - 部开"
               << "视频监控 - 部开" << "飞控套件 - 开源" << "拓展控件 - 基础" << "拓展控件 - 触摸"
               << "弹出窗体 - 开源" << "通用类库 - 开源" << "通用工具 - 开源" << "内置控件 - 开源";
#else
    ui->navListView->setFixedWidth(180);
    listParent << "表盘控件" << "进度控件" << "基础自绘" << "高级自绘"
               << "导航指示" << "波形曲线" << "标尺刻度" << "滑动控件"
               << "柱形控件" << "颜色控件" << "贴图控件" << "其他控件"
               << "视频监控" << "飞控套件" << "拓展控件X" << "拓展控件Y"
               << "弹出窗体" << "通用类库" << "通用工具" << "内置控件";
#endif
}

void frmExamplesFull::initChild()
{
    listChilds[0] << "汽车仪表盘" << "圆弧仪表盘" << "百分比表盘" << "半圆仪表盘" << "进度仪表盘"
                  << "范围仪表盘" << "速度仪表盘" << "时钟仪表盘" << "网络仪表盘" << "简单仪表盘"
                  << "时速仪表盘" << "指南针表盘" << "简易指南针" << "指南针面板" << "旋转仪表盘"
                  << "迷你仪表盘" << "圆环仪表盘" << "飞机仪表盘" << "轨道仪表盘" << "多彩仪表盘"
                  << "云台仪表盘" << "天气仪表盘" << "分贝仪表盘" << "面板仪表盘" << "可输入表盘";

    listChilds[1] << "水波进度条" << "百分比进度" << "圆环进度条" << "等待进度条" << "多彩进度条"
                  << "按钮进度条" << "多态进度条" << "播放进度条" << "环形进度条" << "圆弧进度条"
                  << "光晕进度条" << "提示进度条" << "倒计时进度条";

    listChilds[2] << "自绘电池" << "高亮按钮" << "发光按钮" << "魔法老鼠" << "魔法企鹅"
                  << "魔法小鱼" << "魔法水滴" << "游动的鱼" << "旋转圆形" << "多彩旋转"
                  << "旋转标识" << "开关按钮" << "烤箱按钮"  << "滑动选择" << "滑动日期"
                  << "农历信息" << "农历面板" << "平铺背景" << "手机通讯录";

    listChilds[3] << "自定义多边形" << "自定义摇杆" << "自定义饼状图" << "自定义环形图" << "自定义飞镖盘"
                  << "探探雷达" << "蜘蛛网图" << "光晕日历" << "光晕时钟"
                  << "阴影窗体" << "任务策略表格" << "垂直时间轴" << "横向时间线";

    listChilds[4] << "导航按钮" << "导航标签" << "导航进度条" << "树状导航栏" << "树状导航窗体"
                  << "滑动导航栏" << "滑动导航窗体" << "导航按钮组" << "导航标题栏" << "分页导航";

    listChilds[5] << "直方动态图" << "直方对称图" << "直方波形图" << "波浪曲线" << "简单曲线图"
                  << "声音波形图" << "水波效果图";

    listChilds[6] << "柱状标尺" << "线性标尺" << "滑动标尺" << "双向刻度尺" << "温度计标尺"
                  << "半圆仪标尺" << "进度标尺";

    listChilds[7] << "范围选择条" << "范围滑动条" << "滑动提示条";

    listChilds[8] << "柱状音量条" << "声道音量条";

    listChilds[9] << "颜色面板集合" << "颜色按钮面板" << "颜色滑块面板" << "颜色选取面板" << "颜色多态按钮"
                  << "颜色下拉框" << "样式面板集合";

    listChilds[10] << "广告轮播" << "图片轮播" << "动画按钮" << "设备按钮" << "图片切换" << "图片处理"
                   << "图片开关" << "图片浏览" << "图片背景日历" << "图片背景电池" << "图片背景时钟" << "图片指示灯";

    listChilds[11] << "移动控件" << "面板区域" << "面板窗体" << "LCD时间" << "LCD数码管"
                   << "LED数码管" << "LED文字" << "磁盘容量" << "CPU内存" << "文字滚动"
                   << "验证码" << "图标编辑器" << "IP地址输入框" << "蚂蚁线" << "描点跟随窗体"
                   << "流式布局" << "正方形布局";

    listChilds[12] << "视频监控布局" << "视频监控画面" << "视频回放控件" << "视频窗体控件";

    listChilds[13] << "飞控套件1" << "飞控套件2" << "飞控套件3" << "飞控套件4" << "飞控套件5"
                   << "飞控套件6" << "飞控套件7" << "飞控套件8" << "综合示例";

    listChilds[14] << "高级列表面板" << "视频源面板" << "视频终端面板" << "显示值滑动条"
                   << "自定义进度条" << "自定义下拉框" << "动态堆栈窗体" << "整行选中表格";

    listChilds[15] << "下拉框" << "微调框" << "滚动条" << "选项卡" << "列表控件"
                   << "树状控件" << "表格控件" << "综合示例";

#ifndef Q_OS_ANDROID
    listChilds[16] << "通用控件移动" << "无边框窗体" << "GIF录屏" << "屏幕截图" << "屏幕拾色器"
                   << "通用遮罩层" << "通用状态栏";

    listChilds[17] << "扁平风格" << "汉字转拼音" << "简繁转换" << "Ntp校时" << "日志输出"
                   << "运行时间" << "托盘图标" << "平滑曲线" << "Base64编码" << "图形字体示例"
                   << "城市天气示例" << "省市县联动";

    listChilds[18] << "IP地址工具" << "去除Png警告" << "打字对照板" << "代码行数统计" << "代码生成工具"
                   << "代码拷贝工具" << "Qt源代码拷贝" << "软著代码清理";

    listChilds[19] << "企鹅矢量图" << "颜色拾取" << "矢量颜色" << "放大镜" << "矢量线条" << "关于Qt";
#endif
}

void frmExamplesFull::addItem()
{
    //listItem格式: 标题|父节点标题(父节点为空)|是否展开|提示信息|图标值
    for (int i = 0; i < listParent.count(); i++) {
        addItem(listParent.at(i), listChilds.at(i));
    }

    QString item = listItem.join(",");
    ui->navListView->setItems(item);
    //qDebug() << item;

    //统计控件个数,animationbutton2+bottomwidget+lunarcalendaritem+tumblerdate+tumblertime未单独列出
    //最后关于Qt要减掉
    int count = 5 - 1;
    foreach (QStringList listChild, listChilds) {
        count += listChild.count();
    }

    this->setWindowTitle(QString("Qt自定义控件V1.0 共 %1 个控件 (版权: 刘典武 QQ: 517216493 WX: feiyangqingyun)").arg(count));
    ui->navListView->setCurrentRow(0);
}

void frmExamplesFull::addItem(const QString &parentName, const QStringList &childNames)
{
    //设置节点数据格式: 标题|父节点标题(父节点为空)|是否展开(0展开)|提示信息|左侧图标
    int count = childNames.count();
    listItem << QString("%1||1|%2|").arg(parentName).arg(count);
    for (int i = 0; i < count; i++) {
        listItem << QString("%1. %2|%3|1||0xf0da").arg(i + 1, 2, 10, QChar('0')).arg(childNames.at(i)).arg(parentName);
    }
}

void frmExamplesFull::pressed(const QString &childText, const QString &parentText)
{
    //如果带了 . 表示序号,要删除再比较
    QString text = childText;
    if (text.contains(".")) {
        text = text.mid(text.indexOf(".") + 2, text.length());
    }

    //过滤哪些需要绘制透明背景图
    needDraw = listDraw.contains(text);
    this->update();

    //没有父类名称表示单击的分组则切换到对应控件分组的堆栈窗体
    if (parentText.isEmpty()) {
        ui->stackedWidget->setCurrentIndex(listParent.indexOf(text));
    } else {
        //如果当前窗体的主窗体不在当前则切换过去
        int index = listParent.indexOf(parentText);
        if (ui->stackedWidget->currentIndex() != index) {
            ui->stackedWidget->setCurrentIndex(index);
        }

        if (text == "关于Qt") {
            qApp->aboutQt();
        } else {
            //找到控件分组对应的堆栈窗体
            int index = listParent.indexOf(parentText);
            if (index >= 0) {
                QWidget *widget = widgets.at(index);
                QStringList listChild = listChilds.at(index);
                //找到当前分组的子控件名称
                index = listChild.indexOf(text);
                if (index >= 0) {
                    QMetaObject::invokeMethod(widget, "setIndex", Q_ARG(int, index));
                }
            }
        }
    }
}
