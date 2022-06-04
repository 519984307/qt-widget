#pragma execution_character_set("utf-8")

#include "xcombobox.h"
#include "qlistview.h"
#include "qdebug.h"

XComboBox::XComboBox(QWidget *parent) : QComboBox(parent)
{
    itemWidth = 5;
    itemHeight = 20;
    autoWidth = true;
    this->setView(new QListView());
}

void XComboBox::showEvent(QShowEvent *)
{
    if (autoWidth) {
        //自动计算所有元素,找到最长的元素
        QFontMetrics fm = this->fontMetrics();
        int count = this->count();
        for (int i = 0; i < count; i++) {
            QString text = this->itemText(i);
#if (QT_VERSION >= QT_VERSION_CHECK(5,11,0))
            int textWidth = fm.horizontalAdvance(text);
#else
            int textWidth = fm.width(text);
#endif
            itemWidth = textWidth > itemWidth ? textWidth : itemWidth;
        }

        //宽度增加像素,因为有边距
        this->view()->setFixedWidth(itemWidth + 20);
    }
}

int XComboBox::getItemWidth() const
{
    return this->itemWidth;
}

int XComboBox::getItemHeight() const
{
    return this->itemHeight;
}

bool XComboBox::getAutoWidth() const
{
    return this->autoWidth;
}

void XComboBox::setItemWidth(int itemWidth)
{
    if (this->itemWidth != itemWidth) {
        this->itemWidth = itemWidth;
        if (!autoWidth) {
            this->view()->setFixedWidth(itemWidth);
        }
    }
}

void XComboBox::setItemHeight(int itemHeight)
{
    if (this->itemHeight != itemHeight) {
        this->itemHeight = itemHeight;
        this->setStyleSheet(QString("QComboBox QAbstractItemView::item{min-height:%1px;}").arg(itemHeight));
    }
}

void XComboBox::setAutoWidth(bool autoWidth)
{
    if (this->autoWidth != autoWidth) {
        this->autoWidth = autoWidth;
    }
}
