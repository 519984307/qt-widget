#pragma execution_character_set("utf-8")

#include "progressshadow.h"
#include "qpainter.h"
#include "qdebug.h"

ProgressShadow::ProgressShadow(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;

    precision = 0;
    nullPosition = 90;
    percent = true;

    shadowColor = QColor(34, 37, 47);
    progressColor = QColor(250, 53, 138);
    bgColor = QColor(49, 52, 67);
    textColor = QColor(152, 160, 196);
}

void ProgressShadow::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制背景和光晕
    drawBg(&painter);
    //绘制进度
    drawProgress(&painter);
    //绘制文字
    drawText(&painter);
}

void ProgressShadow::drawBg(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);

    //设置辐射渐变,外围透明度控制产生光晕效果
    QColor color = shadowColor;
    color.setAlpha(100);
    QRadialGradient radialGradient(0, 0, radius, 0, 0);
    radialGradient.setColorAt(0.50, Qt::transparent);
    radialGradient.setColorAt(0.60, color);
    radialGradient.setColorAt(0.67, shadowColor);
    radialGradient.setColorAt(0.69, bgColor);
    radialGradient.setColorAt(0.89, bgColor);
    radialGradient.setColorAt(0.90, shadowColor);
    radialGradient.setColorAt(0.95, color);
    radialGradient.setColorAt(1, Qt::transparent);

    painter->setBrush(radialGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void ProgressShadow::drawProgress(QPainter *painter)
{
    int arcWidth = 3;
    int radius = 95 - arcWidth;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    //设置辐射渐变,外围透明度控制产生光晕效果
    QColor color = progressColor;
    color.setAlpha(100);
    QRadialGradient radialGradient(0, 0, radius, 0, 0);
    radialGradient.setColorAt(0.0, Qt::transparent);
    radialGradient.setColorAt(0.965, color);
    radialGradient.setColorAt(0.975, progressColor);
    radialGradient.setColorAt(0.995, color);
    radialGradient.setColorAt(1, Qt::transparent);

    QPen pen;
    pen.setWidthF(arcWidth);
    pen.setCapStyle(Qt::RoundCap);

    //设置画笔的画刷,产生光晕效果
    //pen.setBrush(radialGradient);
    pen.setColor(progressColor);
    painter->setPen(pen);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angle = 360.0 * ((value - minValue) / (maxValue - minValue));
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    painter->drawArc(rect, (nullPosition - angle) * 16, angle * 16);

    painter->restore();
}

void ProgressShadow::drawText(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(40);
    painter->setFont(font);

    QString text;
    if (percent) {
        double temp = (value - minValue) / (maxValue - minValue) * 100.0;
        text = QString("%1%").arg(temp, 0, 'f', precision);
    } else {
        text = QString("%1").arg((double)value, 0, 'f', precision);
    }

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignCenter, text);

    painter->restore();
}

double ProgressShadow::getMinValue() const
{
    return this->minValue;
}

double ProgressShadow::getMaxValue() const
{
    return this->maxValue;
}

double ProgressShadow::getValue() const
{
    return this->value;
}

int ProgressShadow::getPrecision() const
{
    return this->precision;
}

int ProgressShadow::getNullPosition() const
{
    return this->nullPosition;
}

bool ProgressShadow::getPercent() const
{
    return this->percent;
}

QColor ProgressShadow::getShadowColor() const
{
    return this->shadowColor;
}

QColor ProgressShadow::getProgressColor() const
{
    return this->progressColor;
}

QColor ProgressShadow::getBgColor() const
{
    return this->bgColor;
}

QColor ProgressShadow::getTextColor() const
{
    return this->textColor;
}

QSize ProgressShadow::sizeHint() const
{
    return QSize(200, 200);
}

QSize ProgressShadow::minimumSizeHint() const
{
    return QSize(20, 20);
}

void ProgressShadow::setRange(double minValue, double maxValue)
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

void ProgressShadow::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void ProgressShadow::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void ProgressShadow::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void ProgressShadow::setValue(double value)
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

void ProgressShadow::setValue(int value)
{
    setValue((double)value);
}

void ProgressShadow::setPrecision(int precision)
{
    if (this->precision != precision) {
        this->precision = precision;
        this->update();;
    }
}

void ProgressShadow::setNullPosition(int nullPosition)
{
    if (this->nullPosition != nullPosition) {
        this->nullPosition = nullPosition;
        this->update();;
    }
}

void ProgressShadow::setPercent(bool percent)
{
    if (this->percent != percent) {
        this->percent = percent;
        this->update();;
    }
}

void ProgressShadow::setShadowColor(const QColor &shadowColor)
{
    if (this->shadowColor != shadowColor) {
        this->shadowColor = shadowColor;
        this->update();;
    }
}

void ProgressShadow::setProgressColor(const QColor &progressColor)
{
    if (this->progressColor != progressColor) {
        this->progressColor = progressColor;
        this->update();;
    }
}

void ProgressShadow::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();;
    }
}

void ProgressShadow::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();;
    }
}

