#pragma execution_character_set("utf-8")

#include "progresstip.h"
#include "qpainter.h"
#include "qdebug.h"

ProgressTip::ProgressTip(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;

    percent = true;
    padding = 20;
    radius = 0;

    valueBrush = Qt::NoBrush;
    valueColor = QColor(34, 163, 169);
    bgColor = QColor(100, 100, 100);
    tipColor = QColor(34, 163, 169);
    textColor = QColor(255, 255, 255);
}

void ProgressTip::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制上部分提示信息
    drawTip(&painter);
    //绘制进度
    drawValue(&painter);
}

void ProgressTip::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);

    QRect rect(padding, (height() / 3) * 2, width() - padding * 2, height() / 3);
    painter->drawRoundedRect(rect, radius, radius);

    painter->restore();
}

void ProgressTip::drawTip(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(valueBrush == Qt::NoBrush ? tipColor : valueBrush);

    //计算当前值对应的百分比
    double step = value / (maxValue - minValue);
    int progress = (width() - padding * 2) * step;

    //绘制上部分提示信息背景
    QRect rect(progress, 0, padding * 2, (double)height() / 2.1);
    painter->drawRoundedRect(rect, 2, 2);

    //绘制倒三角
    int centerX = rect.center().x();
    int initY = rect.height();
    int offset = 5;
    QPolygon pts;
    pts.append(QPoint(centerX - offset, initY));
    pts.append(QPoint(centerX + offset, initY));
    pts.append(QPoint(centerX, initY + offset));
    painter->drawPolygon(pts);

    //绘制文字
    QString text;
    if (percent) {
        double temp = (value - minValue) / (maxValue - minValue) * 100.0;
        text = QString("%1%").arg(temp, 0, 'f', 0);
    } else {
        text = QString("%1").arg((double)value, 0, 'f', 0);
    }

    painter->setPen(textColor);
    painter->drawText(rect, Qt::AlignCenter, text);

    painter->restore();
}

void ProgressTip::drawValue(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    //定义了画刷则取画刷,可以形成渐变效果
    painter->setBrush(valueBrush == Qt::NoBrush ? valueColor : valueBrush);

    //计算当前值对应的百分比
    double step = value / (maxValue - minValue);
    int progress = (width() - padding * 2) * step;

    QRect rect(padding, (height() / 3) * 2, progress, height() / 3);
    painter->drawRoundedRect(rect, radius, radius);

    painter->restore();
}

double ProgressTip::getMinValue() const
{
    return this->minValue;
}

double ProgressTip::getMaxValue() const
{
    return this->maxValue;
}

double ProgressTip::getValue() const
{
    return this->value;
}

bool ProgressTip::getPercent() const
{
    return this->percent;
}

int ProgressTip::getPadding() const
{
    return this->padding;
}

int ProgressTip::getRadius() const
{
    return this->radius;
}

QBrush ProgressTip::getValueBrush() const
{
    return this->valueBrush;
}

QColor ProgressTip::getValueColor() const
{
    return this->valueColor;
}

QColor ProgressTip::getBgColor() const
{
    return this->bgColor;
}

QColor ProgressTip::getTipColor() const
{
    return this->tipColor;
}

QColor ProgressTip::getTextColor() const
{
    return this->textColor;
}

QSize ProgressTip::sizeHint() const
{
    return QSize(300, 50);
}

QSize ProgressTip::minimumSizeHint() const
{
    return QSize(50, 30);
}

void ProgressTip::setRange(double minValue, double maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        setValue(minValue);
    } else if (value > maxValue) {
        setValue(maxValue);
    }

    this->update();
}

void ProgressTip::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void ProgressTip::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void ProgressTip::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void ProgressTip::setValue(double value)
{
    //值和当前值一致则无需处理
    if (value == this->value) {
        return;
    }

    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        value = minValue;
    } else if (value > maxValue) {
        value = maxValue;
    }

    this->value = value;
    this->update();
    emit valueChanged(value);
}

void ProgressTip::setValue(int value)
{
    setValue((double)value);
}

void ProgressTip::setPercent(bool percent)
{
    if (this->percent != percent) {
        this->percent = percent;
        this->update();;
    }
}

void ProgressTip::setPadding(int padding)
{
    if (this->padding != padding) {
        this->padding = padding;
        this->update();;
    }
}

void ProgressTip::setRadius(int radius)
{
    if (this->radius != radius) {
        this->radius = radius;
        this->update();;
    }
}

void ProgressTip::setValueBrush(const QBrush &valueBrush)
{
    if (this->valueBrush != valueBrush) {
        this->valueBrush = valueBrush;
        this->update();;
    }
}

void ProgressTip::setValueColor(const QColor &valueColor)
{
    if (this->valueColor != valueColor) {
        this->valueColor = valueColor;
        this->update();;
    }
}

void ProgressTip::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();;
    }
}

void ProgressTip::setTipColor(const QColor &tipColor)
{
    if (this->tipColor != tipColor) {
        this->tipColor = tipColor;
        this->update();;
    }
}

void ProgressTip::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();;
    }
}

