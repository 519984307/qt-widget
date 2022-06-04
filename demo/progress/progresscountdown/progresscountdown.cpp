#pragma execution_character_set("utf-8")

#include "progresscountdown.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"

ProgressCountDown::ProgressCountDown(QWidget *parent) : QWidget(parent)
{
    lineWidth = 8;
    lineColor = QColor(34, 163, 169);

    borderWidth = 8;
    borderColor = QColor(171, 161, 217);

    bgColor = QColor(52, 98, 164);
    textColor = QColor(255, 255, 255);

    value = 0;
    status = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), SLOT(progress()));
}

void ProgressCountDown::mousePressEvent(QMouseEvent *)
{
    if (!timer->isActive()) {
        status = 1;
        value = 0.0;
        timer->start();
    }
}

void ProgressCountDown::paintEvent(QPaintEvent *)
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
    //绘制当前进度
    drawProgress(&painter);
    //绘制文字
    drawText(&painter);
}

void ProgressCountDown::drawBg(QPainter *painter)
{
    int radius = 90 - lineWidth;
    painter->save();

    QPen pen;
    pen.setWidth(borderWidth / 2);
    pen.setColor(borderColor);
    painter->setPen(borderWidth > 0 ? pen : Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void ProgressCountDown::drawProgress(QPainter *painter)
{
    int radius = 99;
    painter->save();

    //绘制圆弧进度
    QPen pen;
    pen.setWidth(lineWidth);
    pen.setColor(lineColor);
    painter->setPen(pen);

    int offset = radius - lineWidth / 2;
    QRectF rect(-offset, -offset, offset * 2, offset * 2);
    int startAngle = offset * 16;
    int spanAngle = -value * 16;
    painter->drawArc(rect, startAngle, spanAngle);

    painter->restore();
}

void ProgressCountDown::drawText(QPainter *painter)
{
    int radius = 99;
    painter->save();

    QFont font;
    int offset = radius - lineWidth / 2 - borderWidth / 2 - 35;
    font.setPixelSize(offset);
    painter->setFont(font);
    painter->setPen(textColor);

    QRect rect(-radius, -radius, radius * 2, radius * 2);
    if (1 == status) {
        QString text = QString("%1%").arg((int)value  * 100 / 360);
        painter->drawText(rect, Qt::AlignCenter, text);
    } else {
        painter->drawText(rect, Qt::AlignCenter, "开 始");
    }

    painter->restore();
}

void ProgressCountDown::progress()
{
    if (1 == status) {
        value += 1.0;
        if (value >= 360) {
            value = 360.0;
            status = 0;
            timer->stop();
        }
    }

    this->update();
}

int ProgressCountDown::getLineWidth() const
{
    return this->lineWidth;
}

QColor ProgressCountDown::getLineColor() const
{
    return this->lineColor;
}

int ProgressCountDown::getBorderWidth() const
{
    return this->borderWidth;
}

QColor ProgressCountDown::getBorderColor() const
{
    return this->borderColor;
}

QColor ProgressCountDown::getBgColor() const
{
    return this->bgColor;
}

QColor ProgressCountDown::getTextColor() const
{
    return this->textColor;
}

QSize ProgressCountDown::sizeHint() const
{
    return QSize(200, 200);
}

QSize ProgressCountDown::minimumSizeHint() const
{
    return QSize(50, 50);
}

void ProgressCountDown::setLineWidth(int lineWidth)
{
    if (this->lineWidth != lineWidth) {
        this->lineWidth = lineWidth;
        this->update();
    }
}

void ProgressCountDown::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->update();
    }
}

void ProgressCountDown::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        this->update();
    }
}

void ProgressCountDown::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        this->update();
    }
}

void ProgressCountDown::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

void ProgressCountDown::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}
