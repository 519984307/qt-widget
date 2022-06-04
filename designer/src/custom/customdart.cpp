#pragma execution_character_set("utf-8")

#include "customdart.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "qmath.h"
#include "qdebug.h"

CustomDart::CustomDart(QWidget *parent) : QWidget(parent)
{
    bgColor = QColor(50, 50, 50);
    textColor = QColor(255, 255, 255);
    fanColor1 = QColor(214, 77, 84);
    fanColor2 = QColor(162, 121, 197);

    fanSize = 10;
    fanOffset = 9;//(360/20)/2
    fanCount = 20;
    fanText = "5|12|9|14|11|8|16|7|19|3|17|2|15|10|6|13|4|18|1|20";
}

CustomDart::~CustomDart()
{
}

void CustomDart::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制背景
    drawBg(&painter);
    //绘制扇形
    drawFan(&painter);
    //绘制文字
    drawText(&painter);
}

void CustomDart::drawBg(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawEllipse(-radius, -radius, radius << 1, radius << 1);
    painter->restore();
}

void CustomDart::drawArc(QPainter *painter, int radius, int angle, int len, const QColor &color)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);

    QRectF rect(-radius, -radius, radius << 1, radius << 1);
    QPainterPath path;
    path.arcTo(rect, angle, len);
    painter->drawPath(path);

    painter->restore();
}

void CustomDart::drawFan(QPainter *painter)
{
    int radius = 80;
    float angle = 360 / fanCount;
    for (int i = 1; i <= fanCount; i++) {
        if (i % 2 == 0) {
            drawArc(painter, radius, fanOffset + angle * i, angle, fanColor1);
            drawArc(painter, radius - fanSize, fanOffset + angle * i,  angle, fanColor2);
            drawArc(painter, radius - 30, fanOffset + angle * i,  angle, fanColor1);
            drawArc(painter, radius - 30 - fanSize, fanOffset + angle * i,  angle, fanColor2);
        } else {
            drawArc(painter, radius, fanOffset + angle * i,  angle, fanColor2);
            drawArc(painter, radius - fanSize, fanOffset + angle * i, angle, fanColor1);
            drawArc(painter, radius - 30, fanOffset + angle * i,  angle, fanColor2);
            drawArc(painter, radius - 30 - fanSize, fanOffset + angle * i,  angle, fanColor1);
        }
    }

    drawArc(painter, radius - 70, 0,  360, fanColor2);
    drawArc(painter, radius - 75, 0,  360, fanColor1);
}

void CustomDart::drawText(QPainter *painter)
{
    int radius = 85;
    painter->save();
    painter->setPen(textColor);

    QStringList list = fanText.split("|");
    for (int i = 1; i <= fanCount; i++) {
        QString text = QString("%1").arg(i);
        //如果扇形数量和扇形文本的数量一致则取设定的文本
        if (fanCount == list.count()) {
            text = list.at(i - 1);
        }

#if (QT_VERSION >= QT_VERSION_CHECK(5,11,0))
        int textWidth = painter->fontMetrics().horizontalAdvance(text);
#else
        int textWidth = painter->fontMetrics().width(text);
#endif
        painter->rotate(-360 / fanCount);
        painter->drawText(-textWidth / 2, -radius, text);
    }

    painter->restore();
}

QColor CustomDart::getBgColor() const
{
    return this->bgColor;
}

QColor CustomDart::getTextColor() const
{
    return this->textColor;
}

QColor CustomDart::getFanColor1() const
{
    return this->fanColor1;
}

QColor CustomDart::getFanColor2() const
{
    return this->fanColor2;
}

int CustomDart::getFanSize() const
{
    return this->fanSize;
}

int CustomDart::getFanOffset() const
{
    return this->fanOffset;
}

int CustomDart::getFanCount() const
{
    return this->fanCount;
}

QString CustomDart::getFanText() const
{
    return this->fanText;
}

QSize CustomDart::sizeHint() const
{
    return QSize(500, 500);
}

QSize CustomDart::minimumSizeHint() const
{
    return QSize(100, 100);
}

void CustomDart::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

void CustomDart::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}

void CustomDart::setFanColor1(const QColor &fanColor1)
{
    if (this->fanColor1 != fanColor1) {
        this->fanColor1 = fanColor1;
        this->update();
    }
}

void CustomDart::setFanColor2(const QColor &fanColor2)
{
    if (this->fanColor2 != fanColor2) {
        this->fanColor2 = fanColor2;
        this->update();
    }
}

void CustomDart::setFanSize(int fanSize)
{
    if (this->fanSize != fanSize) {
        this->fanSize = fanSize;
        this->update();
    }
}

void CustomDart::setFanOffset(int fanOffset)
{
    if (this->fanOffset != fanOffset) {
        this->fanOffset = fanOffset;
        this->update();
    }
}

void CustomDart::setFanCount(int fanCount)
{
    //限定扇形数量最小值以及必须是偶数
    if (this->fanCount != fanCount && fanCount >= 4 && fanCount % 2 == 0) {
        this->fanCount = fanCount;
        this->update();
    }
}

void CustomDart::setFanText(const QString &fanText)
{
    if (this->fanText != fanText) {
        this->fanText = fanText;
        this->update();
    }
}

