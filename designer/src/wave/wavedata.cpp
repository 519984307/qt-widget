#pragma execution_character_set("utf-8")

#include "wavedata.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "qevent.h"
#include "smoothcurve.h"
#include "qfile.h"
#include "qdatetime.h"
#include "qdebug.h"

WaveData::WaveData(QWidget *parent) : QWidget(parent)
{
    deep = 0.5;
    showLine = false;
    lineWidth = 5;

    bgColor = QColor(255, 255, 255);
    lineColor = QColor(255, 107, 107);
    dataColor = QColor(100, 184, 255);
    dataColor2 = QColor(34, 163, 169);
    dataColor3 = QColor(162, 121, 197);
    waveStyle = WaveStyle_Line;

    length = 100;
    position = 0;
}

void WaveData::mousePressEvent(QMouseEvent *e)
{
    if (!showLine || data.count() <= 0) {
        return;
    }

    //计算当前按下处的位置,切换到当前位置
    int x = e->pos().x();
    position = ((double)x / width()) * length;
    this->update();
    emit positionChanged(position);
}

void WaveData::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制数据
    drawData(&painter, data, dataColor);
    drawData(&painter, data2, dataColor2);
    drawData(&painter, data3, dataColor3);
    //绘制当前位置线条
    drawLine(&painter);
}

void WaveData::drawBg(QPainter *painter)
{
    painter->save();
    painter->fillRect(this->rect(), bgColor);
    painter->restore();
}

void WaveData::drawData(QPainter *painter, const QVector<float> &data, const QColor &dataColor)
{
    if (data.count() == 0) {
        return;
    }

    painter->save();

    //获取最大值最小值
    float max = data.at(0);
    float min = data.at(0);
    int count = data.count();

    for (int i = 1; i < count; i++) {
        if (max < data.at(i)) {
            max = data.at(i);
        }

        if (min > data.at(i)) {
            min = data.at(i);
        }
    }

    //转化成当前屏幕的内的坐标大小
    max += deep;
    min -= deep;

    //自动转换数据到屏幕坐标位置
    QVector<QPointF> points;
    for (int i = 0; i < count; i++) {
        qreal x = i * width() / count;
        qreal y = height() - (((data.at(i) - min) / (max - min)) * height());
        points.append(QPointF(x, y));
    }

    //绘制不同的风格
    if (waveStyle == WaveStyle_Line) {
        painter->setPen(dataColor);
        for (int i = 0; i < count - 1; i++) {
            painter->drawLine(points.at(i), points.at(i + 1));
        }
    } else if (waveStyle == WaveStyle_Smooth) {
        painter->setPen(dataColor);
        QPainterPath path = SmoothCurve::createSmoothCurve(points);
        painter->drawPath(path);
    } else if (waveStyle == WaveStyle_Bar) {
        qreal penWidth = width() / (count * 1.6);
        QPen pen = painter->pen();
        pen.setColor(dataColor);
        pen.setWidthF(penWidth);
        pen.setCapStyle(Qt::RoundCap);
        painter->setPen(pen);

        for (int i = 0; i < count; i++) {
            QPointF point = points.at(i);
            qreal x = point.x() + penWidth / 1.2;
            painter->drawLine(QPointF(x, point.y()), QPointF(x, height()));
        }
    }

    painter->restore();
}

void WaveData::drawLine(QPainter *painter)
{
    if (!showLine || position > length || data.count() <= 0) {
        return;
    }

    painter->save();

    QPen pen;
    pen.setWidth(lineWidth);
    pen.setColor(lineColor);
    painter->setPen(pen);

    //计算当前位置对应的坐标
    int x = ((double)position / length) * width();
    painter->drawLine(x, 0, x, height());

    painter->restore();
}

double WaveData::getDeep() const
{
    return this->deep;
}

bool WaveData::getShowLine() const
{
    return this->showLine;
}

int WaveData::getLineWidth() const
{
    return this->lineWidth;
}

QColor WaveData::getBgColor() const
{
    return this->bgColor;
}

QColor WaveData::getLineColor() const
{
    return this->lineColor;
}

QColor WaveData::getDataColor() const
{
    return this->dataColor;
}

QColor WaveData::getDataColor2() const
{
    return this->dataColor2;
}

QColor WaveData::getDataColor3() const
{
    return this->dataColor3;
}

WaveData::WaveStyle WaveData::getWaveStyle() const
{
    return this->waveStyle;
}

int WaveData::getLength() const
{
    return this->length;
}

int WaveData::getPosition() const
{
    return this->position;
}

QVector<float> WaveData::getData() const
{
    return this->data;
}

QVector<float> WaveData::getData2() const
{
    return this->data2;
}

QVector<float> WaveData::getData3() const
{
    return this->data3;
}

QSize WaveData::sizeHint() const
{
    return QSize(500, 300);
}

QSize WaveData::minimumSizeHint() const
{
    return QSize(50, 30);
}

void WaveData::setDeep(double deep)
{
    if (this->deep != deep) {
        this->deep = deep;
        this->update();
    }
}

void WaveData::setShowLine(bool showLine)
{
    if (this->showLine != showLine) {
        this->showLine = showLine;
        this->update();
    }
}

void WaveData::setLineWidth(int lineWidth)
{
    if (this->lineWidth != lineWidth) {
        this->lineWidth = lineWidth;
        this->update();
    }
}

void WaveData::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->update();
    }
}

void WaveData::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

void WaveData::setDataColor(const QColor &dataColor)
{
    if (this->dataColor != dataColor) {
        this->dataColor = dataColor;
        this->update();
    }
}

void WaveData::setDataColor2(const QColor &dataColor2)
{
    if (this->dataColor2 != dataColor2) {
        this->dataColor2 = dataColor2;
        this->update();
    }
}

void WaveData::setDataColor3(const QColor &dataColor3)
{
    if (this->dataColor3 != dataColor3) {
        this->dataColor3 = dataColor3;
        this->update();
    }
}

void WaveData::setWaveStyle(const WaveData::WaveStyle &waveStyle)
{
    if (this->waveStyle != waveStyle) {
        this->waveStyle = waveStyle;
        this->update();
    }
}

void WaveData::setLength(int length)
{
    if (this->length != length) {
        this->length = length;
        this->position = 0;
        this->update();
    }
}

void WaveData::setPosition(int position)
{
    if (this->position != position && position <= length) {
        this->position = position;
        this->update();
    }
}

void WaveData::setData(const QVector<float> &data)
{
    this->data = data;
    this->update();
}

void WaveData::setData2(const QVector<float> &data2)
{
    this->data2 = data2;
    this->update();
}

void WaveData::setData3(const QVector<float> &data3)
{
    this->data3 = data3;
    this->update();
}

void WaveData::clearData()
{
    this->data.clear();
    this->data2.clear();
    this->data3.clear();
    this->update();
}
