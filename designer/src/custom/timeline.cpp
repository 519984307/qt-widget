#pragma execution_character_set("utf-8")
#include "timeline.h"
#include "qpainter.h"
#include "qevent.h"
#include "qdebug.h"

TimeLine::TimeLine(QWidget *parent)	: QWidget(parent)
{
    scaled = 1;
    lineHeight = 10;

    lineColor = QColor("#f39c12");
    bgColor = QColor("#2c3e50");

    mousePressed = false;
    containsPath = false;

    startTime = TimeLineTime(0, 0, 0, 0, 20);
    currentTime = TimeLineTime(10, 10, 10, 0, 0);

    //设置鼠标指针为手掌
    setCursor(Qt::OpenHandCursor);
}

TimeLine::~TimeLine()
{

}

void TimeLine::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform);
    //采用双缓冲的机制先绘制到图片上最后绘制图片
    painter.drawPixmap(0, 0, timeLinePix);
    painter.drawPixmap(0, 0, timeLinePosPix);
    //qDebug() << startTime << currentTime;
}

void TimeLine::drawBgColor(QPainter *painter)
{
    painter->save();
    painter->setBrush(bgColor);
    painter->drawRect(this->rect());
    painter->restore();
}

void TimeLine::drawBottomLine(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(lineColor, 2));
    painter->drawLine(0, this->height(), this->width(), this->height());
    painter->restore();
}

void TimeLine::drawScaleLine(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);
    getUnitValue();
    int scaledWidth = getScaledWidth();

    qreal posx1 = startPair.first;
    while (true) {
        if (posx1 < -100) {
            break;
        }
        drawScaleLine(painter, posx1, posx1 - scaledWidth);
        posx1 -= scaledWidth;
    }

    while (true) {
        if (posx1 > this->width() + 100) {
            break;
        }
        drawScaleLine(painter, posx1, posx1 + scaledWidth);
        posx1 += scaledWidth;
    }

    painter->restore();
}

void TimeLine::drawScaleLine(QPainter *painter, qreal posx1, qreal posx2)
{
    QString timetext;
    int subLineCount = 0;
    timetext = getTimeForPosx(posx1).toString(timeLineUnit);

    if (timeLineUnit == TimeLineUnit_Msecs) {
        if (scaled > 80) {
            subLineCount = 10;
        } else if (scaled > 75) {
            subLineCount = 5;
        } else {
            subLineCount = 2;
        }
    } else if (timeLineUnit == TimeLineUnit_Second) {
        if (scaled > 60) {
            subLineCount = 10;
        } else if (scaled > 55) {
            subLineCount = 5;
        } else {
            subLineCount = 2;
        }
    } else if (timeLineUnit == TimeLineUnit_Minute) {
        if (scaled > 35) {
            subLineCount = 8;
        } else if (scaled > 30) {
            subLineCount = 4;
        } else {
            subLineCount = 2;
        }
    } else if (timeLineUnit == TimeLineUnit_Hour) {
        if (scaled > 15) {
            subLineCount = 8;
        } else if (scaled > 5) {
            subLineCount = 4;
        } else {
            subLineCount = 2;
        }
    }

    //绘制主刻度线
    painter->drawLine(QPointF(posx1, this->height()), QPointF(posx1, this->height() - 10));
    //绘制时间文本
    QFontMetrics metric(painter->font());
    QRect textrect = metric.boundingRect(timetext);
    painter->drawText(posx1 - textrect.width() / 2, this->height() - 16, timetext);

    //绘制子刻度线
    if (subLineCount <= 0) {
        return;
    }

    qreal subScaledWidth = qAbs(posx1 - posx2) * 1.0 / subLineCount;
    for (int i = 1; i < subLineCount; i++) {
        QPointF point1(posx1 + subScaledWidth * i, this->height());
        QPointF point2(posx1 + subScaledWidth * i, this->height() - lineHeight);
        painter->drawLine(point1, point2);
    }
}

void TimeLine::zoomIn(int posx)
{
    TimeLineTime postime = getTimeForPosx(posx);
    scaled++;
    scaled = qMin(99, scaled);
    adjustTimeForPosx(posx, postime);
}

void TimeLine::zoomOut(int posx)
{
    TimeLineTime postime = getTimeForPosx(posx);
    scaled--;
    scaled = qMax(1, scaled);
    adjustTimeForPosx(posx, postime);
}

void TimeLine::adjustTimeForPosx(int posx, TimeLineTime postime)
{
    getUnitValue();

    TimeLineTime time;
    int scaledWidth = getScaledWidth();
    qreal scaleCount = posx * -1.0 / scaledWidth;
    if (timeLineUnit == TimeLineUnit_Msecs) {
        time = postime.addUsto(scaleCount * 1000);
    } else if (timeLineUnit == TimeLineUnit_Second) {
        time = postime.addUsto(scaleCount * 1000000);
    } else if (timeLineUnit == TimeLineUnit_Minute) {
        time = postime.addUsto(scaleCount * 60000000);
    } else if (timeLineUnit == TimeLineUnit_Hour) {
        time = postime.addUsto(scaleCount * 3600000000);
    }

    setStartTime(time);
}

void TimeLine::wheelEvent(QWheelEvent *event)
{
    //判断鼠标滚轮方向放大和缩小
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    if (event->angleDelta().y() > 0) {
        zoomIn(event->position().x());
    } else {
        zoomOut(event->position().x());
    }
#else
    if (event->delta() > 0) {
        zoomIn(event->pos().x());
    } else {
        zoomOut(event->pos().x());
    }
#endif

    //限定在范围内
    if (!startTime.isValid()) {
        setStartTime(TimeLineTime(0));
    }
}

TimeLine::TimeLineTime TimeLine::getTimeForPosx(qreal posx)
{
    TimeLineTime time;
    int scaledwidth = getScaledWidth();
    qreal scaleCount = (posx - startPair.first) * 1.0 / scaledwidth;
    if (timeLineUnit == TimeLineUnit_Msecs) {
        time = startPair.second.addUsto(scaleCount * 1000);
    } else if (timeLineUnit == TimeLineUnit_Second) {
        time = startPair.second.addUsto(scaleCount * 1000000);
    } else if (timeLineUnit == TimeLineUnit_Minute) {
        time = startPair.second.addUsto(scaleCount * 60000000);
    } else if (timeLineUnit == TimeLineUnit_Hour) {
        time = startPair.second.addUsto(scaleCount * 3600000000);
    }
    return time;
}

TimeLine::TimeLineTime TimeLine::getOffsetUcs(int offsetx)
{
    TimeLineTime time;
    int scaledWidth = getScaledWidth();
    qreal scaleCount = offsetx * 1.0 / scaledWidth;
    if (timeLineUnit == TimeLineUnit_Msecs) {
        time = timePressed.addUsto(scaleCount * 1000);
    } else if (timeLineUnit == TimeLineUnit_Second) {
        time = timePressed.addUsto(scaleCount * 1000000);
    } else if (timeLineUnit == TimeLineUnit_Minute) {
        time = timePressed.addUsto(scaleCount * 60000000);
    } else if (timeLineUnit == TimeLineUnit_Hour) {
        time = timePressed.addUsto(scaleCount * 3600000000);
    }

    return time;
}

void TimeLine::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button()) {
        mousePressed = true;
        pointPressed = event->pos();
        timePressed = getStartTime();
        setCursor(Qt::ClosedHandCursor);
        setCurrentTime(getTimeForPosx(event->pos().x()));
        this->update();
    }
}

void TimeLine::mouseMoveEvent(QMouseEvent *event)
{
    if (timeLinePosPath.contains(event->pos())) {
        containsPath = true;
        setCursor(Qt::PointingHandCursor);
    } else if (!mousePressed) {
        containsPath = false;
        setCursor(Qt::OpenHandCursor);
    }

    if (mousePressed) {
        if (containsPath) {
            setCurrentTime(getTimeForPosx(event->pos().x()));
            this->update();
        } else {
            TimeLineTime time = getOffsetUcs(pointPressed.x() - event->pos().x());
            setStartTime(time);
        }
    }
}

void TimeLine::mouseReleaseEvent(QMouseEvent *)
{
    if (mousePressed) {
        mousePressed = false;
        setCursor(Qt::OpenHandCursor);
        if (!startTime.isValid()) {
            setStartTime(TimeLineTime(0));
        }
    }
}

void TimeLine::resizeEvent(QResizeEvent *)
{
    setStartTime(startTime);
}

qreal TimeLine::getPosxForTime(const TimeLineTime &time)
{
    int scaledWidth = getScaledWidth();
    qreal posx = 0;

    if (timeLineUnit == TimeLineUnit_Msecs) {
        posx = startTime.usTo(time) * scaledWidth / 1000.0;
    } else if (timeLineUnit == TimeLineUnit_Second) {
        posx = startTime.usTo(time) * scaledWidth / 1000000.0;
    } else if (timeLineUnit == TimeLineUnit_Minute) {
        posx = startTime.usTo(time) * scaledWidth / 60000000.0;
    } else if (timeLineUnit == TimeLineUnit_Hour) {
        posx = startTime.usTo(time) * scaledWidth / 3600000000.0;
    }

    return posx;
}

void TimeLine::getUnitValue()
{
    qreal startPosX;
    TimeLineTime time;
    int scaledWidth = getScaledWidth();

    if (scaled >= 75) {
        time = TimeLineTime(startTime.hour(), startTime.minute(), startTime.second(), startTime.msecs());
        startPosX = time.usTo(startTime) * scaledWidth / 1000.0;
        timeLineUnit = TimeLine::TimeLineUnit_Msecs;
    } else if (scaled >= 50) {
        time = TimeLineTime(startTime.hour(), startTime.minute(), startTime.second());
        startPosX = time.usTo(startTime) * scaledWidth / 1000000.0;
        timeLineUnit = TimeLine::TimeLineUnit_Second;
    } else if (scaled >= 25) {
        time = TimeLineTime(startTime.hour(), startTime.minute());
        startPosX = time.usTo(startTime) * scaledWidth / 60000000.0;
        timeLineUnit = TimeLine::TimeLineUnit_Minute;
    } else {
        time = TimeLineTime(startTime.hour(), 0);
        startPosX = time.usTo(startTime) * scaledWidth / 3600000000.0;
        timeLineUnit = TimeLine::TimeLineUnit_Hour;
    }

    startPosX *= -1.0;
    startPair = qMakePair(startPosX, time);
}

int TimeLine::getScaled() const
{
    return this->scaled;
}

int TimeLine::getScaledWidth() const
{
    return scaled % 25 * 10 + 100;
}

void TimeLine::setScaled(int scaled)
{
    if (this->scaled != scaled) {
        this->scaled = scaled;
        setStartTime(startTime);
        this->update();
    }
}

int TimeLine::getLineHeight() const
{
    return this->lineHeight;
}

void TimeLine::setLineHeight(int lineHeight)
{
    if (this->lineHeight != lineHeight) {
        this->lineHeight = lineHeight;
        setStartTime(startTime);
        this->update();
    }
}

QColor TimeLine::getLineColor() const
{
    return this->lineColor;
}

void TimeLine::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        setStartTime(startTime);
        this->update();
    }
}

QColor TimeLine::getBgColor() const
{
    return this->bgColor;
}

void TimeLine::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        setStartTime(startTime);
        this->update();
    }
}

TimeLine::TimeLineTime TimeLine::getStartTime() const
{
    return startTime;
}

void TimeLine::setStartTime(const TimeLineTime &time)
{
    startTime = time;
    QPixmap tmpPixmap(this->size());
    tmpPixmap.fill(Qt::transparent);

    QPainter painter(&tmpPixmap);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景色
    drawBgColor(&painter);
    //绘制底线
    drawBottomLine(&painter);
    //绘制刻度线
    drawScaleLine(&painter);
    //绘制时间线
    setCurrentTime(currentTime);

    timeLinePix = tmpPixmap;
    this->update();
}

TimeLine::TimeLineTime TimeLine::getCurrentTime() const
{
    return currentTime;
}

void TimeLine::setCurrentTime(const TimeLineTime &time)
{
    if (currentTime.ds != time.ds) {
        emit timeLineChanged(time);
    }

    currentTime = time;
    timeLinePosPath = QPainterPath();
    qreal posx = getPosxForTime(time);
    QPixmap tmpPixmap(this->size());
    tmpPixmap.fill(Qt::transparent);

    if (posx >= -10 && posx <= this->width() + 10) {
        QPainter painter(&tmpPixmap);
        painter.setPen(lineColor);
        painter.setBrush(lineColor);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

        //上下两个小三角形
        QPolygonF arrowPolygonF1;
        arrowPolygonF1 << QPointF(posx - 6, 0) << QPointF(posx + 6, 0) << QPointF(posx, 6);
        QPolygonF arrowPolygonF2;
        arrowPolygonF2 << QPointF(posx - 6, this->height()) << QPointF(posx + 6, this->height()) << QPointF(posx, this->height() - 6);

        timeLinePosPath.setFillRule(Qt::WindingFill);
        timeLinePosPath.addPolygon(arrowPolygonF1);
        timeLinePosPath.moveTo(QPointF(posx, 6));
        timeLinePosPath.lineTo(posx + 0.5, this->height() - 6);
        timeLinePosPath.addPolygon(arrowPolygonF2);
        timeLinePosPath.closeSubpath();
        painter.drawPath(timeLinePosPath);
    }

    timeLinePosPix = tmpPixmap;
    //this->update();
}

QSize TimeLine::sizeHint() const
{
    return QSize(400, 80);
}

QSize TimeLine::minimumSizeHint() const
{
    return QSize(100, 40);
}
