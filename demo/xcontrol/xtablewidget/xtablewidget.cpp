#include "xtablewidget.h"
#include "qheaderview.h"
#include "qdebug.h"

XTableWidget::XTableWidget(QWidget *parent) : QTableWidget(parent)
{
    previousRow = -1;
    textColor = QColor(0, 0, 0);
    //textColor = palette().color(QPalette::WindowText);
    hoverBgColor = QColor(162, 121, 197);
    hoverTextColor = QColor(255, 255, 255);

    //开启鼠标追踪
    this->setMouseTracking(true);
    //选中单元格行为为选中整行
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //关联单元格进入事件,进行颜色的处理
    connect(this, SIGNAL(cellEntered(int, int)), this, SLOT(cellEntered(int, int)));
}

void XTableWidget::leaveEvent(QEvent *)
{
    //还原上一行的颜色
    QTableWidgetItem *currentItem = item(previousRow, 0);
    if (currentItem != NULL) {
        setRowColor(previousRow, Qt::transparent, textColor);
    }
}

void XTableWidget::cellEntered(int row, int column)
{
    leaveEvent(NULL);

    //设置当前行的颜色
    QTableWidgetItem *currentItem = item(row, column);
    if (currentItem != NULL && !currentItem->isSelected()) {
        setRowColor(row, hoverBgColor, hoverTextColor);
    }

    //设置上一行的索引为当前行
    previousRow = row;
}

void XTableWidget::setRowColor(int row, const QColor &bgColor, const QColor &textColor)
{
    //对指定行的所有单元格设置统一颜色
    for (int i = 0; i < columnCount(); i++) {
        QTableWidgetItem *currentItem = item(row, i);
        currentItem->setBackground(bgColor);
        currentItem->setForeground(textColor);
    }
}

QColor XTableWidget::getTextColor() const
{
    return this->textColor;
}

QColor XTableWidget::getHoverBgColor() const
{
    return this->hoverBgColor;
}

QColor XTableWidget::getHoverTextColor() const
{
    return this->hoverTextColor;
}

void XTableWidget::setTextColor(const QColor &color)
{
    this->textColor = color;
}

void XTableWidget::setHoverBgColor(const QColor &color)
{
    this->hoverBgColor = color;
}

void XTableWidget::setHoverTextColor(const QColor &color)
{
    this->hoverTextColor = color;
}
