#pragma execution_character_set("utf-8")

#include "progressarc.h"
#include "qpainter.h"
#include "qmath.h"
#include "qdebug.h"

ProgressArc::ProgressArc(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 0;

    startAngle = 45;
    endAngle = 45;

    arcColor = QColor(34, 163, 169);
    textColor = QColor(34, 163, 169);
    titleColor = QColor(50, 50, 50);
    baseColor = QColor(180, 180, 180);
    bgColor = Qt::transparent;

    percent = true;
    arcWidth = 20;
    title = "正确率";
}

ProgressArc::~ProgressArc()
{
}

void ProgressArc::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    if (bgColor != Qt::transparent) {
        painter.setPen(Qt::NoPen);
        painter.fillRect(this->rect(), bgColor);
    }

    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制圆弧
    drawArc(&painter);
    //绘制当前值
    drawValue(&painter);
    //绘制标题
    drawTitle(&painter);
}

void ProgressArc::drawArc(QPainter *painter)
{
    int radius = 99 - arcWidth;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    QPen pen;
    pen.setWidthF(arcWidth);
    pen.setCapStyle(Qt::RoundCap);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0 - startAngle - endAngle;
    double angleCurrent = angleAll * ((value - minValue) / (maxValue - minValue));
    double angleOther = angleAll - angleCurrent;
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);

    //绘制圆弧背景
    pen.setColor(baseColor);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    //绘制圆弧进度
    pen.setColor(arcColor);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);

    painter->restore();
}

void ProgressArc::drawValue(QPainter *painter)
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

    QRectF textRect(-radius, 0, radius * 2, radius / 3);
    painter->drawText(textRect, Qt::AlignCenter, text);

    painter->restore();
}

void ProgressArc::drawTitle(QPainter *painter)
{
    double radius = 100;
    painter->save();
    painter->setPen(titleColor);

    QFont font;
    font.setPixelSize(25);
    painter->setFont(font);

    QRectF textRect(-radius, -radius / 2.5, radius * 2, radius / 3);
    painter->drawText(textRect, Qt::AlignCenter, title);

    painter->restore();
}

double ProgressArc::getMinValue() const
{
    return this->minValue;
}

double ProgressArc::getMaxValue() const
{
    return this->maxValue;
}

double ProgressArc::getValue() const
{
    return this->value;
}

int ProgressArc::getPrecision() const
{
    return this->precision;
}

int ProgressArc::getStartAngle() const
{
    return this->startAngle;
}

int ProgressArc::getEndAngle() const
{
    return this->endAngle;
}

QColor ProgressArc::getArcColor() const
{
    return this->arcColor;
}

QColor ProgressArc::getTextColor() const
{
    return this->textColor;
}

QColor ProgressArc::getTitleColor() const
{
    return this->titleColor;
}

QColor ProgressArc::getBaseColor() const
{
    return this->baseColor;
}

QColor ProgressArc::getBgColor() const
{
    return this->bgColor;
}

bool ProgressArc::getPercent() const
{
    return this->percent;
}

int ProgressArc::getArcWidth() const
{
    return this->arcWidth;
}

QString ProgressArc::getTitle() const
{
    return this->title;
}

QSize ProgressArc::sizeHint() const
{
    return QSize(200, 200);
}

QSize ProgressArc::minimumSizeHint() const
{
    return QSize(50, 50);
}

void ProgressArc::setRange(double minValue, double maxValue)
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

void ProgressArc::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void ProgressArc::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void ProgressArc::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void ProgressArc::setValue(double value)
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

void ProgressArc::setValue(int value)
{
    setValue((double)value);
}

void ProgressArc::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        this->update();
    }
}

void ProgressArc::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        this->update();
    }
}

void ProgressArc::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        this->update();
    }
}

void ProgressArc::setArcColor(const QColor &arcColor)
{
    if (this->arcColor != arcColor) {
        this->arcColor = arcColor;
        this->update();
    }
}

void ProgressArc::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}

void ProgressArc::setTitleColor(const QColor &titleColor)
{
    if (this->titleColor != titleColor) {
        this->titleColor = titleColor;
        this->update();
    }
}

void ProgressArc::setBaseColor(const QColor &baseColor)
{
    if (this->baseColor != baseColor) {
        this->baseColor = baseColor;
        this->update();
    }
}

void ProgressArc::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

void ProgressArc::setPercent(bool percent)
{
    if (this->percent != percent) {
        this->percent = percent;
        this->update();
    }
}

void ProgressArc::setArcWidth(int arcWidth)
{
    if (arcWidth > 0 && arcWidth <= 30 && this->arcWidth != arcWidth) {
        this->arcWidth = arcWidth;
        this->update();
    }
}

void ProgressArc::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        this->update();
    }
}
