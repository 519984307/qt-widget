#pragma execution_character_set("utf-8")

#include "gaugecompass2.h"
#include "qpainter.h"
#include "qmath.h"
#include "qdebug.h"

GaugeCompass2::GaugeCompass2(QWidget *parent) : QWidget(parent)
{
    value = 0;
    scaleMajor = 36;
    scaleMinor = 1;

    scaleColor = QColor(0, 0, 0);
    pointerColor = QColor(253, 139, 40);
    circleColor1 = QColor(100, 100, 100);
    circleColor2 = QColor(250, 250, 250);
    textColor = QColor(0, 0, 0);

    QFont font;
    font.setFamily("Arial");
    font.setPixelSize(7);
    setFont(font);
}

GaugeCompass2::~GaugeCompass2()
{

}

void GaugeCompass2::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制刻度线
    drawScale(&painter);
    //绘制刻度值
    drawScaleNum(&painter);
    //绘制中心园
    drawCircle(&painter);
    //绘制NS文字
    drawText(&painter);
    //绘制指针
    drawPointer(&painter);
}

void GaugeCompass2::drawScale(QPainter *painter)
{
    int radius = 99;
    painter->save();

    painter->rotate(0);
    int steps = (scaleMajor * scaleMinor);
    double angleStep = 360.0 / steps;

    QPen pen;
    pen.setColor(scaleColor);
    pen.setCapStyle(Qt::RoundCap);

    //分别绘制大刻度和小刻度
    for (int i = 0; i <= steps; i++) {
        if (i % scaleMinor == 0) {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 2, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void GaugeCompass2::drawScaleNum(QPainter *painter)
{
    int radius = 85;
    painter->save();
    painter->setPen(scaleColor);

    //旋转角度值决定文字的开始绘制的地方
    int angle = -90;
    double startRad = (360 - angle) * (M_PI / 180);
    double deltaRad = (360 - 0) * (M_PI / 180) / scaleMajor;

    for (int i = 0; i <= scaleMajor; i++) {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 1.0 * i * (360.0 / scaleMajor);
        //这里可以过滤0或者360因为重叠了
        if (value == 0) {
            continue;
        }

        QString text = QString::number(value);
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

void GaugeCompass2::drawCircle(QPainter *painter)
{
    int radius = 50;
    painter->save();

    //设置圆锥渐变
    QConicalGradient gradient(0, 0, 90);
    gradient.setColorAt(0, circleColor1);
    gradient.setColorAt(1, circleColor2);

    //采用对画笔设置渐变颜色的形式
    //很多人以为QPen只能设置单色
    QPen pen;
    pen.setBrush(gradient);
    pen.setWidth(20);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

    //绘制圆环
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void GaugeCompass2::drawText(QPainter *painter)
{
    int radius = 60;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(15);
    font.setBold(true);
    painter->setFont(font);

    //不用绝对定位而是通过矩形区域指定文字对齐的方式绘制文字非常巧妙
    //哪些文字不需要可以注释掉
    QRect textRect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignTop | Qt::AlignHCenter, "N");
    painter->drawText(textRect, Qt::AlignBottom | Qt::AlignHCenter, "S");

    radius -= 2;
    textRect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, "W");

    radius -= 2;
    textRect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, "E");

    painter->restore();
}

void GaugeCompass2::drawPointer(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    //先旋转到初始值然后在旋转到目标值
    painter->rotate(-180);
    painter->rotate(value);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

double GaugeCompass2::getValue() const
{
    return this->value;
}

int GaugeCompass2::getScaleMajor() const
{
    return this->scaleMajor;
}

int GaugeCompass2::getScaleMinor() const
{
    return this->scaleMinor;
}

QColor GaugeCompass2::getScaleColor() const
{
    return this->scaleColor;
}

QColor GaugeCompass2::getPointerColor() const
{
    return this->pointerColor;
}

QColor GaugeCompass2::getCircleColor1() const
{
    return this->circleColor1;
}

QColor GaugeCompass2::getCircleColor2() const
{
    return this->circleColor2;
}

QColor GaugeCompass2::getTextColor() const
{
    return this->textColor;
}

QSize GaugeCompass2::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeCompass2::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeCompass2::setValue(double value)
{
    //值和当前值一致则无需处理
    if (value == this->value) {
        return;
    }

    this->value = value;
    this->update();
    emit valueChanged(value);
}

void GaugeCompass2::setValue(int value)
{
    setValue((double)value);
}

void GaugeCompass2::setScaleMajor(int scaleMajor)
{
    if (scaleMajor > 0 && this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        this->update();
    }
}

void GaugeCompass2::setScaleMinor(int scaleMinor)
{
    if (scaleMinor > 0 && this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        this->update();
    }
}

void GaugeCompass2::setScaleColor(const QColor &scaleColor)
{
    if (this->scaleColor != scaleColor) {
        this->scaleColor = scaleColor;
        this->update();
    }
}

void GaugeCompass2::setPointerColor(const QColor &pointerColor)
{
    if (this->pointerColor != pointerColor) {
        this->pointerColor = pointerColor;
        this->update();
    }
}

void GaugeCompass2::setCircleColor1(const QColor &circleColor1)
{
    if (this->circleColor1 != circleColor1) {
        this->circleColor1 = circleColor1;
        this->update();
    }
}

void GaugeCompass2::setCircleColor2(const QColor &circleColor2)
{
    if (this->circleColor2 != circleColor2) {
        this->circleColor2 = circleColor2;
        this->update();
    }
}

void GaugeCompass2::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}


