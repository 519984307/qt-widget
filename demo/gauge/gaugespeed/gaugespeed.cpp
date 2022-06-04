#pragma execution_character_set("utf-8")

#include "gaugespeed.h"
#include "qpainter.h"
#include "qmath.h"
#include "qvariantanimation.h"
#include "qpropertyanimation.h"
#include "qlcdnumber.h"
#include "qdebug.h"

GaugeSpeed::GaugeSpeed(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 2;
    digitCount = 5;

    scaleMajor = 8;
    scaleMinor = 1;
    startAngle = 50;
    endAngle = 50;

    animation = false;
    animationDuration = 800;
    animationType = QEasingCurve::OutQuad;

    ringWidth = 10;
    ringPercentStart = 25;
    ringPercentMid = 50;
    ringPercentEnd = 25;

    ringColorStart = QColor(2, 242, 177);
    ringColorMid = QColor(45, 196, 248);
    ringColorEnd = QColor(254, 68, 138);

    pointerColor = QColor(178, 221, 253);
    bgColor = Qt::transparent;
    textColor = QColor(50, 50, 50);
    unit = "M";
    text = "Mbps";

    //实例化属性机制产生线性插值数据
    currentValue = value;
    animate = new QPropertyAnimation(this, "animationValue");

    //显示数码管
    lcd = new QLCDNumber(this);
    lcd->setDigitCount(digitCount);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->setFrameShape(QFrame::NoFrame);
    lcd->setStyleSheet(QString("color:%1;").arg(textColor.name()));
}

GaugeSpeed::~GaugeSpeed()
{

}

void GaugeSpeed::resizeEvent(QResizeEvent *)
{
    int width = this->width();
    int height = this->height();
    int lcdWidth = width / 3.5;
    int lcdHeight = height / 6;
    lcd->setGeometry((width - lcdWidth) / 2, height - (2.0 * lcdHeight), lcdWidth, lcdHeight);
}

void GaugeSpeed::paintEvent(QPaintEvent *)
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

    //绘制圆环
    checkPercent();
    drawRing(&painter);

    //绘制刻度线
    drawScale(&painter);

    //绘制刻度值
    drawScaleNum(&painter);

    //根据指示器形状绘制指示器
    drawPointer(&painter);

    //绘制当前值
    drawValue(&painter);
}

void GaugeSpeed::drawRing(QPainter *painter)
{
    int radius = 100;
    painter->save();

    QPen pen;
    pen.setCapStyle(Qt::FlatCap);
    pen.setWidthF(ringWidth);

    radius = radius - ringWidth;
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);

    //计算总范围角度,根据占比例自动计算三色圆环范围角度
    double angleAll = 360.0 - startAngle - endAngle;
    double angleStart = angleAll * (double)ringPercentStart / 100;
    double angleMid = angleAll * (double)ringPercentMid / 100;
    double angleEnd = angleAll * (double)ringPercentEnd / 100;

    //绘制第一圆环
    pen.setColor(ringColorStart);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleStart) * 16, angleStart * 16);

    //绘制第二圆环
    pen.setColor(ringColorMid);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleStart - angleMid) * 16, angleMid * 16);

    //绘制第三圆环
    pen.setColor(ringColorEnd);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleStart - angleMid - angleEnd) * 16, angleEnd * 16);

    painter->restore();
}

void GaugeSpeed::drawScale(QPainter *painter)
{
    int radius = 94;
    painter->save();

    QPen pen;
    pen.setColor(textColor);
    pen.setCapStyle(Qt::RoundCap);

    painter->rotate(startAngle);
    int steps = (scaleMajor * scaleMinor);
    double angleStep = (360.0 - startAngle - endAngle) / steps;

    //计算圆环对应大刻度范围索引
    int indexStart = steps * (double)ringPercentStart / 100 + 1;
    int indexMid = steps * (double)ringPercentMid / 100 - 1;
    int indexEnd = steps * (double)ringPercentEnd / 100 + 1;
    int index = 0;

    for (int i = 0; i <= steps; i++) {
        if (i % scaleMinor == 0) {
            //根据所在圆环范围切换颜色
            if (index < indexStart) {
                pen.setColor(ringColorStart);
            } else if (index < (indexStart + indexMid)) {
                pen.setColor(ringColorMid);
            } else if (index < (indexStart + indexMid + indexEnd)) {
                pen.setColor(ringColorEnd);
            }

            index++;

            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 13, 0, radius);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void GaugeSpeed::drawScaleNum(QPainter *painter)
{
    int radius = 70;
    painter->save();
    painter->setPen(textColor);

    double startRad = (360 - startAngle - 90) * (M_PI / 180);
    double deltaRad = (360 - startAngle - endAngle) * (M_PI / 180) / scaleMajor;

    for (int i = 0; i <= scaleMajor; i++) {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 1.0 * i * ((maxValue - minValue) / scaleMajor) + minValue;

        QString text = QString("%1%2").arg((double)value, 0, 'f', 0).arg(unit);
#if (QT_VERSION >= QT_VERSION_CHECK(5,11,0))
        double textWidth = fontMetrics().horizontalAdvance(text);
#else
        double textWidth = fontMetrics().width(text);
#endif
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, text);
    }

    painter->restore();
}

void GaugeSpeed::drawPointer(QPainter *painter)
{
    int radius = 62;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(4, -5, 0, 0, -8, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeSpeed::drawValue(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QRectF rect(-radius, radius / 6, radius * 2, radius / 6);

    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);
    painter->drawText(rect, Qt::AlignCenter, text);

    QString text = QString("%1").arg((double)currentValue, 0, 'f', precision);
    text = QString("%1").arg(text, 5, QChar('0'));

#if 0
    lcd->setVisible(false);
    QRectF textRect(-radius, radius / 2.3, radius * 2, radius / 3);
    font.setPixelSize(20);
    painter->setFont(font);
    painter->drawValue(textRect, Qt::AlignCenter, text);
#else
    lcd->display(text);
#endif

    painter->restore();
}

void GaugeSpeed::checkPercent()
{
    //校验圆环所占比例,加起来不能超过100,如果超过则自动恢复默认值
    if (ringPercentStart + ringPercentMid + ringPercentEnd > 100) {
        ringPercentStart = 25;
        ringPercentMid = 50;
        ringPercentEnd = 25;
    }
}

double GaugeSpeed::getMinValue() const
{
    return this->minValue;
}

double GaugeSpeed::getMaxValue() const
{
    return this->maxValue;
}

double GaugeSpeed::getValue() const
{
    return this->value;
}

double GaugeSpeed::getAnimationValue() const
{
    return this->value;
}

int GaugeSpeed::getPrecision() const
{
    return this->precision;
}

int GaugeSpeed::getDigitCount() const
{
    return this->digitCount;
}

int GaugeSpeed::getScaleMajor() const
{
    return this->scaleMajor;
}

int GaugeSpeed::getScaleMinor() const
{
    return this->scaleMinor;
}

int GaugeSpeed::getStartAngle() const
{
    return this->startAngle;
}

int GaugeSpeed::getEndAngle() const
{
    return this->endAngle;
}

bool GaugeSpeed::getAnimation() const
{
    return this->animation;
}

int GaugeSpeed::getAnimationDuration() const
{
    return this->animationDuration;
}

QEasingCurve GaugeSpeed::getAnimationType() const
{
    return this->animationType;
}

int GaugeSpeed::getRingWidth() const
{
    return this->ringWidth;
}

int GaugeSpeed::getRingPercentStart() const
{
    return this->ringPercentStart;
}

int GaugeSpeed::getRingPercentMid() const
{
    return this->ringPercentMid;
}

int GaugeSpeed::getRingPercentEnd() const
{
    return this->ringPercentEnd;
}

QColor GaugeSpeed::getRingColorStart() const
{
    return this->ringColorStart;
}

QColor GaugeSpeed::getRingColorMid() const
{
    return this->ringColorMid;
}

QColor GaugeSpeed::getRingColorEnd() const
{
    return this->ringColorEnd;
}

QColor GaugeSpeed::getPointerColor() const
{
    return this->pointerColor;
}

QColor GaugeSpeed::getBgColor() const
{
    return this->bgColor;
}

QColor GaugeSpeed::getTextColor() const
{
    return this->textColor;
}

QString GaugeSpeed::getUnit() const
{
    return this->unit;
}

QString GaugeSpeed::getText() const
{
    return this->text;
}

QSize GaugeSpeed::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeSpeed::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeSpeed::setRange(double minValue, double maxValue)
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

void GaugeSpeed::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeSpeed::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeSpeed::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeSpeed::setValue(double value)
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

    //必须要先设置值然后用 currentValue 去改变值
    this->value = value;
    emit valueChanged(value);

    if (!animation) {
        this->currentValue = value;
        this->update();
    } else {
        //启用动画机制
        animate->stop();
        animate->setDuration(animationDuration);
        animate->setEasingCurve(animationType);
        animate->setStartValue(this->currentValue);
        animate->setEndValue(value);
        animate->start();
    }
}

void GaugeSpeed::setValue(int value)
{
    setValue((double)value);
}

void GaugeSpeed::setAnimationValue(double value)
{
    this->currentValue = value;
    this->update();
}

void GaugeSpeed::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        this->update();
    }
}

void GaugeSpeed::setDigitCount(int digitCount)
{
    if (this->digitCount != digitCount) {
        this->digitCount = digitCount;
        lcd->setDigitCount(digitCount);
        this->update();
    }
}

void GaugeSpeed::setScaleMajor(int scaleMajor)
{
    if (scaleMajor > 0 && this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        this->update();
    }
}

void GaugeSpeed::setScaleMinor(int scaleMinor)
{
    if (scaleMinor > 0 && this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        this->update();
    }
}

void GaugeSpeed::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        this->update();
    }
}

void GaugeSpeed::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        this->update();
    }
}

void GaugeSpeed::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        this->update();
    }
}

void GaugeSpeed::setAnimationDuration(int animationDuration)
{
    if (this->animationDuration != animationDuration) {
        this->animationDuration = animationDuration;
        this->update();
    }
}

void GaugeSpeed::setAnimationType(const QEasingCurve &animationType)
{
    if (this->animationType != animationType) {
        this->animationType = animationType;
        this->update();
    }
}

void GaugeSpeed::setRingWidth(int ringWidth)
{
    if (this->ringWidth != ringWidth) {
        this->ringWidth = ringWidth;
        this->update();
    }
}

void GaugeSpeed::setRingPercentStart(int ringPercentStart)
{
    if (ringPercentStart > 0 && this->ringPercentStart != ringPercentStart) {
        this->ringPercentStart = ringPercentStart;
        this->update();
    }
}

void GaugeSpeed::setRingPercentMid(int ringPercentMid)
{
    if (ringPercentMid > 0 && this->ringPercentMid != ringPercentMid) {
        this->ringPercentMid = ringPercentMid;
        this->update();
    }
}

void GaugeSpeed::setRingPercentEnd(int ringPercentEnd)
{
    if (ringPercentEnd > 0 && this->ringPercentEnd != ringPercentEnd) {
        this->ringPercentEnd = ringPercentEnd;
        this->update();
    }
}

void GaugeSpeed::setRingColorStart(const QColor &ringColorStart)
{
    if (this->ringColorStart != ringColorStart) {
        this->ringColorStart = ringColorStart;
        this->update();
    }
}

void GaugeSpeed::setRingColorMid(const QColor &ringColorMid)
{
    if (this->ringColorMid != ringColorMid) {
        this->ringColorMid = ringColorMid;
        this->update();
    }
}

void GaugeSpeed::setRingColorEnd(const QColor &ringColorEnd)
{
    if (this->ringColorEnd != ringColorEnd) {
        this->ringColorEnd = ringColorEnd;
        this->update();
    }
}

void GaugeSpeed::setPointerColor(const QColor &pointerColor)
{
    if (this->pointerColor != pointerColor) {
        this->pointerColor = pointerColor;
        this->update();
    }
}

void GaugeSpeed::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

void GaugeSpeed::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        lcd->setStyleSheet(QString("color:%1;").arg(textColor.name()));
        this->textColor = textColor;
        this->update();
    }
}

void GaugeSpeed::setUnit(const QString &unit)
{
    if (this->unit != unit) {
        this->unit = unit;
        this->update();
    }
}

void GaugeSpeed::setText(const QString &text)
{
    if (this->text != text) {
        this->text = text;
        this->update();
    }
}
