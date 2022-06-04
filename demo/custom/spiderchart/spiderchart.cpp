#pragma execution_character_set("utf-8")

#include "spiderchart.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "qmath.h"
#include "qdebug.h"

SpiderChart::SpiderChart(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;

    levelCount = 5;
    sideCount = 7;
    sideColor = QColor(100, 100, 100);
    sideText = "A|B|C|D|E|F|G";

    startAngle = 270;
    scalePos = 0;
    scaleVisible = true;
    legendVisible = true;

    lineWidth = 0.5;
    lineColor = QColor(100, 100, 100);
    textColor = QColor(100, 100, 100);
}

SpiderChart::~SpiderChart()
{

}

void SpiderChart::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    radius = 80;
    radiusPer = (double)radius / levelCount;
    startRad = (360 - startAngle) * (M_PI / 180);
    deltaRad = 360 * (M_PI / 180) / sideCount;

    //绘制多边形
    drawSide(&painter);
    //绘制线条
    drawLine(&painter);
    //绘制种类描述
    drawText(&painter);
    //绘制标尺
    drawScale(&painter);
    //绘制数据图案
    drawValue(&painter);
    //绘制图例
    drawLegend(&painter);
}

void SpiderChart::drawSide(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setWidthF(lineWidth);
    pen.setColor(sideColor);
    painter->setPen(pen);

    int x, y;
    double sina, cosa;
    for (int j = 0 ; j < levelCount ; j++) {
        float newR = radiusPer * (j + 1);
        QPolygonF polygon;
        for (int i = 0; i < sideCount; i++) {
            sina = sin(startRad - i * deltaRad);
            cosa = cos(startRad - i * deltaRad);
            x = newR * cosa;
            y = -newR * sina;
            polygon.append(QPointF(x, y));
        }

        painter->drawPolygon(polygon);
    }

    painter->restore();
}

void SpiderChart::drawLine(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setWidthF(lineWidth);
    pen.setColor(lineColor);
    painter->setPen(pen);

    int x, y;
    double sina, cosa;
    for (int i = 0; i < sideCount; i++) {
        sina = sin(startRad - i * deltaRad);
        cosa = cos(startRad - i * deltaRad);
        x = radius * cosa;
        y = -radius * sina;
        painter->drawLine(QPointF(0, 0), QPointF(x, y));
    }

    painter->restore();
}

void SpiderChart::drawText(QPainter *painter)
{
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(7);
    painter->setFont(font);
    QFontMetrics fm = painter->fontMetrics();
    QStringList listText = sideText.split("|");

    int x, y;
    double sina, cosa;
    for (int i = 0; i < sideCount; i++) {
        sina = sin(startRad - i * deltaRad);
        cosa = cos(startRad - i * deltaRad);
        x = radius * cosa;
        y = -radius * sina;

        QRectF textRect;
        QString text = "null";
        if (i < listText.count()) {
            text = listText.at(i);
        }

        int textHeight = fm.height();
#if (QT_VERSION >= QT_VERSION_CHECK(5,11,0))
        int textWidth = fm.horizontalAdvance(text);
#else
        int textWidth = fm.width(text);
#endif
        //分8个方向
        if (x == 0 && y > 0) {//正下
            textRect = QRectF(x - textWidth / 2, y, textWidth, textHeight);
        } else if (x == 0 && y < 0) {//正上
            textRect = QRectF(x - textWidth / 2, y - textHeight, textWidth, textHeight);
        } else if (x > 0 && y == 0) {//正右
            textRect = QRectF(x, y - textHeight / 2, textWidth, textHeight);
        } else if (x < 0 && y == 0) {//正左
            textRect = QRectF(x - textWidth, y - textHeight / 2, textWidth, textHeight);
        } else if (x > 0 && y > 0) {//右下
            textRect = QRectF(x, y, textWidth, textHeight);
        } else if (x > 0 && y < 0) {//右上
            textRect = QRectF(x, y - textHeight, textWidth, textHeight);
        } else if (x < 0 && y < 0) {//左上
            textRect = QRectF(x - textWidth, y - textHeight, textWidth, textHeight);
        } else if (x < 0 && (y > 0)) {//左下
            textRect = QRectF(x - textWidth, y, textWidth, textHeight);
        } else {
            textRect = QRectF(x, y, textWidth, textHeight);
        }

        painter->drawText(textRect, Qt::AlignCenter | Qt::AlignTop, text);
    }

    painter->restore();
}

void SpiderChart::drawScale(QPainter *painter)
{
    if (!scaleVisible) {
        return;
    }

    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(5);
    painter->setFont(font);
    QFontMetrics fm = painter->fontMetrics();
    float scaleStep = (maxValue - minValue) / levelCount * 1.0;

    int x, y;
    double sina, cosa;
    for (int j = 0 ; j < levelCount + 1 ; j++) {
        if (j <= 0) {
            x = 0.0;
            y = 0.0;
        } else {
            float newR = radiusPer * j;
            sina = sin(startRad - scalePos * deltaRad);
            cosa = cos(startRad - scalePos * deltaRad);
            x = newR * cosa;
            y = -newR * sina;
        }

        QString scaleNum = QString::number(scaleStep * j + minValue, 'f', 0);
        int textHeight = fm.height();
#if (QT_VERSION >= QT_VERSION_CHECK(5,11,0))
        int textWidth = fm.horizontalAdvance(scaleNum);
#else
        int textWidth = fm.width(scaleNum);
#endif
        QRectF textRect = QRectF(x - textWidth - 2, y, textWidth, textHeight);
        painter->drawText(textRect, Qt::AlignCenter | Qt::AlignTop, scaleNum);
    }

    painter->restore();
}

void SpiderChart::drawValue(QPainter *painter)
{
    painter->save();

    int x, y;
    double sina, cosa;
    mdata::const_iterator it = dataValue.constBegin();
    while (it != dataValue.constEnd()) {
        QColor color = dataColor.value(it.key());
        QPen dataPen;
        color.setAlpha(150);
        dataPen.setColor(color);
        dataPen.setWidthF(1.5);
        painter->setPen(dataPen);

        QPolygonF polygon;
        QVector<float> data = it.value();
        for (int j = 0 ; j < sideCount; j++) {
            sina = sin(startRad - j * deltaRad);
            cosa = cos(startRad - j * deltaRad);

            double r, value;
            if (j >= data.size()) {
                value = minValue;
                r = qAbs(minValue / (maxValue - minValue)) * radius;
            } else {
                value = data.at(j) ;
                if (value < minValue) {
                    value = minValue;
                } else if (value > maxValue) {
                    value = maxValue;
                }
            }

            r = qAbs((value - minValue) / (maxValue - minValue))  * radius;
            x = r * cosa;
            y = -r * sina;

            QPointF point(x, y);
            polygon.append(point);
            painter->drawPoint(point);
        }

        QPainterPath painterPath;
        painterPath.addPolygon(polygon);
        painterPath.closeSubpath();

        //区域边框颜色加深里边半透明
        color.setAlpha(255);
        dataPen.setColor(color);
        dataPen.setWidthF(lineWidth);
        painter->setPen(dataPen);
        color.setAlpha(100);
        painter->setBrush(color);
        painter->drawPath(painterPath);
        ++it;
    }

    painter->restore();
}

void SpiderChart::drawLegend(QPainter *painter)
{
    if (!legendVisible) {
        return;
    }

    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(5);
    painter->setFont(font);
    QFontMetrics fm = painter->fontMetrics();

    //找到值中文本最大宽度
    int maxW = 0;
    mdata::const_iterator it = dataValue.constBegin();
    while (it != dataValue.constEnd()) {
#if (QT_VERSION >= QT_VERSION_CHECK(5,11,0))
        int textWidth = fm.horizontalAdvance(it.key());
#else
        int textWidth = fm.width(it.key());
#endif
        if (textWidth > maxW) {
            maxW = textWidth;
        }
        ++it;
    }

    int i = 0;
    float sx = 100 - 1;
    float sy = -100 + 1;
    mdata::const_iterator it2 = dataValue.constBegin();
    while (it2 != dataValue.constEnd()) {
        QString text = it2.key();
        int textHeight = fm.height();
#if (QT_VERSION >= QT_VERSION_CHECK(5,11,0))
        int textWidth = fm.horizontalAdvance(text);
#else
        int textWidth = fm.width(text);
#endif
        QRectF legendNameRect = QRectF(sx - maxW, sy + (textHeight + 1) * i, textWidth, textHeight);
        QRectF legendColorRect = QRectF(sx - maxW - 1.5 - textHeight, sy + (textHeight + 1) * i, textHeight, textHeight);
        painter->drawText(legendNameRect, Qt::AlignCenter | Qt::AlignTop, text);
        painter->fillRect(legendColorRect, dataColor.value(text));
        i++;
        ++it2;
    }

    painter->restore();
}

qreal SpiderChart::getMinValue() const
{
    return this->minValue;
}

qreal SpiderChart::getMaxValue() const
{
    return this->maxValue;
}

int SpiderChart::getLevelCount() const
{
    return this->levelCount;
}

int SpiderChart::getSideCount() const
{
    return this->sideCount;
}

QColor SpiderChart::getSideColor() const
{
    return this->sideColor;
}

QString SpiderChart::getSideText() const
{
    return this->sideText;
}

int SpiderChart::getStartAngle() const
{
    return this->startAngle;
}

int SpiderChart::getScalePos() const
{
    return this->scalePos;
}

bool SpiderChart::getScaleVisible() const
{
    return this->scaleVisible;
}

bool SpiderChart::getLegendVisible() const
{
    return this->legendVisible;
}

qreal SpiderChart::getLineWidth() const
{
    return this->lineWidth;
}

QColor SpiderChart::getLineColor() const
{
    return this->lineColor;
}

QColor SpiderChart::getTextColor() const
{
    return this->textColor;
}

QSize SpiderChart::sizeHint() const
{
    return QSize(500, 500);
}

QSize SpiderChart::minimumSizeHint() const
{
    return QSize(100, 100);
}

void SpiderChart::setMinValue(qreal minValue)
{
    if (this->minValue != minValue) {
        this->minValue = minValue;
        this->update();
    }
}

void SpiderChart::setMaxValue(qreal maxValue)
{
    if (this->maxValue != maxValue) {
        this->maxValue = maxValue;
        this->update();
    }
}

void SpiderChart::setRange(qreal minValue, qreal maxValue)
{
    setMinValue(minValue);
    setMaxValue(maxValue);
}

void SpiderChart::setLevelCount(int levelCount)
{
    if (this->levelCount != levelCount && levelCount > 0) {
        this->levelCount = levelCount;
        this->update();
    }
}

void SpiderChart::setSideCount(int sideCount)
{
    //限定最小3条边
    if (this->sideCount != sideCount && sideCount >= 3) {
        this->sideCount = sideCount;
        this->update();
    }
}

void SpiderChart::setSideColor(const QColor &sideColor)
{
    if (this->sideColor != sideColor) {
        this->sideColor = sideColor;
        this->update();
    }
}

void SpiderChart::setSideText(const QString &sideText)
{
    if (this->sideText != sideText) {
        this->sideText = sideText;
        this->update();
    }
}

void SpiderChart::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        this->update();
    }
}

void SpiderChart::setScalePos(int scalePos)
{
    if (this->scalePos != scalePos && scalePos >= 0 && scalePos < sideCount) {
        this->scalePos = scalePos;
        this->update();
    }
}

void SpiderChart::setScaleVisible(bool scaleVisible)
{
    if (this->scaleVisible != scaleVisible) {
        this->scaleVisible = scaleVisible;
        this->update();
    }
}

void SpiderChart::setLegendVisible(bool legendVisible)
{
    if (this->legendVisible != legendVisible) {
        this->legendVisible = legendVisible;
        this->update();
    }
}

void SpiderChart::setLineWidth(qreal lineWidth)
{
    if (this->lineWidth != lineWidth) {
        this->lineWidth = lineWidth;
        this->update();
    }
}

void SpiderChart::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->update();
    }
}

void SpiderChart::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}

void SpiderChart::addData(const QString &name, const QVector<float> &data, const QColor &color)
{
    dataValue[name] = data;
    dataColor[name] = color;
    this->update();
}

void SpiderChart::setDataColor(const QString &name, const QColor &color)
{
    dataColor[name] = color;
    this->update();
}

void SpiderChart::removeData(const QString &name)
{
    dataValue.remove(name);
    dataColor.remove(name);
    this->update();
}

void SpiderChart::clearData()
{
    dataValue.clear();
    dataColor.clear();
    this->update();
}
