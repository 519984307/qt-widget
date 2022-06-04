#pragma execution_character_set("utf-8")

#include "shadowcalendar.h"
#include "qpainter.h"
#include "qdebug.h"

ShadowCalendar::ShadowCalendar(QWidget *parent)	: QWidget(parent)
{
    bgColor = QColor("#212425");
    textColor = QColor("#FFFFFF");
    shadowColor = QColor("#FFFFFF");
    selectColor = QColor("#0078D7");

    //首次主动设置日期
    this->updateCalendar(QDate::currentDate());

    //开启鼠标追踪
    this->setMouseTracking(true);
}

ShadowCalendar::~ShadowCalendar()
{
}

void ShadowCalendar::updateCalendar(const QDate &selectDate)
{
    if (this->selectDate != selectDate) {
        int row = 0;
        DateItem dateItem[6][7];
        QDate date(selectDate.year(), selectDate.month(), 1);
        while (date.month() == selectDate.month()) {
            int weekDay = date.dayOfWeek();
            dateItem[row][weekDay - 1].year = date.year();
            dateItem[row][weekDay - 1].month = date.month();
            dateItem[row][weekDay - 1].day = date.day();
            date = date.addDays(1);
            if (weekDay == 7 && date.month() == date.month()) {
                row++;
            }
        }

        //重新赋值
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                this->dateItem[i][j] = dateItem[i][j];
            }
        }

        this->selectDate = selectDate;
        this->update();
    }
}

void ShadowCalendar::leaveEvent(QEvent *)
{
    this->update();
}

void ShadowCalendar::mouseMoveEvent(QMouseEvent *)
{
    this->update();
}

void ShadowCalendar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    int sw = 336;
    int sh = 336;
    qreal scaleX = this->width() * 1.0 / sw;
    qreal scaleY = this->height() * 1.0 / sh;

    painter.scale(scaleX, scaleY);
    painter.setPen(Qt::NoPen);
    painter.fillRect(0, 0, sw, sh, bgColor);

    qreal iw = sw / 7.0;
    qreal ih = sh / 7.0;

    //mask
    QPointF globalpoint = this->mapFromGlobal(QCursor::pos());
    const QPointF &point = QPointF(globalpoint.x() / scaleX, globalpoint.y() / scaleY);

    //绘制光晕背景
    if (this->underMouse()) {
        int effectradius = 58;
        painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        QRadialGradient radialGrad(point, effectradius);
        radialGrad.setColorAt(0, QColor(0, 0, 0, 120));
        radialGrad.setColorAt(1, QColor(0, 0, 0, 255));
        painter.setBrush(radialGrad);
        painter.drawEllipse(point, effectradius, effectradius);

        painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
        painter.setBrush(Qt::NoBrush);

        for (int row = 0; row < 6; row++) {
            for (int column = 0; column < 7; column++) {
                QRectF rect = QRectF(column * iw, (row + 1) * ih, iw, ih).adjusted(3, 3, -3, -3);
                if (rect.contains(point)) {
                    painter.save();
                    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
                    painter.setPen(QPen(QColor(220, 220, 220, 160), 2));
                    painter.drawRoundedRect(rect, 2, 2);
                    painter.restore();
                    continue;
                } else {
                    painter.setPen(QPen(shadowColor, 2));
                }

                painter.drawRoundedRect(rect, 2, 2);
            }
        }

        //绘制圆形的光晕底层背景
        painter.fillRect(0, 0, sw, sh, QColor(200, 200, 200, 50));
    }

    //绘制头部中文数字,先设置图像叠加模式为源在上面
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.setPen(textColor);
    QStringList listHead;
    listHead << "一" << "二" << "三" << "四" << "五" << "六" << "日";
    for (int i = 0; i < 7; i++) {
        painter.drawText(i * iw, 0, iw, ih, Qt::AlignCenter, listHead.at(i));
    }

    //绘制日期
    for (int row = 0; row < 6; row++) {
        for (int column = 0; column < 7; column++) {
            if (dateItem[row][column].day > 0) {
                QRectF rect = QRectF(column * iw, (row + 1) * ih, iw, ih).adjusted(3, 3, -3, -3);

                //如果是选中的日期则突出绘制背景
                if (QDate::currentDate() == QDate(dateItem[row][column].year, dateItem[row][column].month, dateItem[row][column].day)) {
                    painter.setPen(QPen(selectColor, 2));
                    painter.setBrush(Qt::NoBrush);

                    //如果和光晕效果重叠则边框高亮
                    if (rect.contains(point)) {
                        painter.setPen(QPen(selectColor.lighter(), 2));
                    }

                    //绘制圆角边框
                    painter.drawRoundedRect(rect, 2, 2);

                    //绘制里边背景
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(selectColor);
                    painter.drawRoundedRect(rect.adjusted(4, 4, -4, -4), 2, 2);
                }

                painter.setPen(textColor);
                painter.drawText(rect, Qt::AlignCenter, QString::number(dateItem[row][column].day));
            }
        }
    }
}

QColor ShadowCalendar::getBgColor() const
{
    return this->bgColor;
}

QColor ShadowCalendar::getTextColor() const
{
    return this->textColor;
}

QColor ShadowCalendar::getShadowColor() const
{
    return this->shadowColor;
}

QColor ShadowCalendar::getSelectColor() const
{
    return this->selectColor;
}

QSize ShadowCalendar::sizeHint() const
{
    return QSize(370, 355);
}

QSize ShadowCalendar::minimumSizeHint() const
{
    return QSize(100, 85);
}

void ShadowCalendar::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

void ShadowCalendar::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}

void ShadowCalendar::setShadowColor(const QColor &shadowColor)
{
    if (this->shadowColor != shadowColor) {
        this->shadowColor = shadowColor;
        this->update();
    }
}

void ShadowCalendar::setSelectColor(const QColor &selectColor)
{
    if (this->selectColor != selectColor) {
        this->selectColor = selectColor;
        this->update();
    }
}
