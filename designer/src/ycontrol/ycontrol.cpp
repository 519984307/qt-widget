#include "ycontrol.h"

void YControl::initStyle(QWidget *widget)
{
    //设置样式表
    QStringList list;

    //悬浮滚动条样式
    int scrollWidth = 12;
    QString bgColor = QString("rgba(179,179,198,255)");
    QString handleColor = QString("rgba(124,124,150,255)");

    //垂直滚动条
    list << QString("QScrollBar#vscrollBar:vertical{background:%1;padding:0px;min-width:%2px;max-width:%2px;}")
            .arg(bgColor).arg(scrollWidth);
    list << QString("QScrollBar#vscrollBar::handle:vertical{background:%1;min-height:100px;border-radius:%2px;}")
            .arg(handleColor).arg(scrollWidth / 2);
    list << QString("QScrollBar#vscrollBar::handle:vertical:hover{background:%1;}").arg(handleColor);
    list << QString("QScrollBar#vscrollBar::handle:vertical:pressed{background:%1;}").arg(handleColor);
    list << QString("QScrollBar#vscrollBar::add-page:vertical{background:none;}");
    list << QString("QScrollBar#vscrollBar::sub-page:vertical{background:none;}");
    list << QString("QScrollBar#vscrollBar::add-line:vertical{background:none;}");
    list << QString("QScrollBar#vscrollBar::sub-line:vertical{background:none;}");

    //左右滚动条
    list << QString("QScrollBar#hscrollBar:horizontal{background:%1;padding:0px;min-height:%2px;max-height:%2px;}")
            .arg(bgColor).arg(scrollWidth);
    list << QString("QScrollBar#hscrollBar::handle:horizontal{background:%1;min-width:100px;border-radius:%2px;}")
            .arg(handleColor).arg(scrollWidth / 2);
    list << QString("QScrollBar#hscrollBar::handle:horizontal:hover{background:%1;}").arg(handleColor);
    list << QString("QScrollBar#hscrollBar::handle:horizontal:pressed{background:%1;}").arg(handleColor);
    list << QString("QScrollBar#hscrollBar::add-page:horizontal{background:none;}");
    list << QString("QScrollBar#hscrollBar::sub-page:horizontal{background:none;}");
    list << QString("QScrollBar#hscrollBar::add-line:horizontal{background:none;}");
    list << QString("QScrollBar#hscrollBar::sub-line:horizontal{background:none;}");

    //列表元素
    int itemHeight = 35;
    list << QString("QAbstractItemView::item{min-height:%1px;margin:2px;color:#000000;background:#B3B3C6;}").arg(itemHeight);
    list << QString("QAbstractItemView::item:hover{background:#FFCC33;}");

    //表格头部样式
    list << QString("QHeaderView::section,QTableCornerButton:section{color:%1;background:%2;border:1px solid %1;}").arg("#FFFFFF").arg("#7C7C96");

    //选项卡样式
    int tabBorderWidth = 3;
    list << QString("QTabWidget::pane{border:%1px solid %2;background:%3;}").arg(tabBorderWidth).arg("#FFCC33").arg("#D6D8DC");
    list << QString("QTabBar::tab{color:#000000;background:#B7B8C3;min-height:50px;min-width:100px;}");
    list << QString("QTabBar::tab:selected{margin-bottom:-%1px;padding-bottom:%1px;border:%1px solid %2;background:%3;}").arg(tabBorderWidth).arg("#FFCC33").arg("#D6D8DC");
    list << QString("QTabBar::tab:!selected{border-bottom:%1px solid %2;}").arg(tabBorderWidth).arg("#FFCC33");
    list << QString("QTabWidget::pane:top{top:-%1px;}QTabWidget::pane:bottom{bottom:-%1px;}QTabWidget::pane:left{right:-%1px;}QTabWidget::pane:right{left:-%1px;}").arg(tabBorderWidth);

    list<<QString("*{font:%1px;}").arg(16);
    widget->setStyleSheet(list.join(""));
    //widget->setPalette(QPalette("#FF0000"));
}
