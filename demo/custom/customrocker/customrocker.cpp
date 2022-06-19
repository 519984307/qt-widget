/**
 * @file customrocker.cpp
 * @author creekwater
 * @brief
 *
 * 摇杆控件
 *
 * 1. 可设置是否只在外边缘线上。
 * 2. 可设置边框宽度。
 * 3. 可设置摇杆的半径。
 * 4. 可设置边框颜色。
 * 5. 可设置背景颜色。
 * 6. 可设置摇杆颜色。
 * 7. 发出移动角度信号。
 *
 * @version 0.1
 * @date 2022-06-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma execution_character_set("utf-8")

#include "customrocker.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmath.h"
#include "qdebug.h"

CustomRocker::CustomRocker(QWidget *parent) : QWidget(parent)
{
    online = false;
    borderWidth = 5;
    rockerRadius = 20;

    borderColor = QColor(14, 153, 160);
    bgColor = QColor(14, 153, 160, 50);
    rockerColor = QColor(34, 163, 169);

    pressed = false;
}

void CustomRocker::resizeEvent(QResizeEvent *)
{
    int w = this->width() / 2;
    int h = this->height() / 2;
    if (w > 0 && h > 0) {
        //大圆的半径要减去摇杆的半径
        radius = qMin(w, h) - rockerRadius - 2 - 1;
        currentPoint = centerPoint = QPoint(w, h);
    }
}

void CustomRocker::mousePressEvent(QMouseEvent *e)
{
    pressed = true;
    resetPoint(e->pos());
    this->update();
}

void CustomRocker::mouseMoveEvent(QMouseEvent *e)
{
    if (pressed) {
        resetPoint(e->pos());
        this->update();
    }
}

void CustomRocker::mouseReleaseEvent(QMouseEvent *)
{
    pressed = false;
    currentPoint = centerPoint;
    this->update();
}

double CustomRocker::twoPtDistance(const QPointF &pt1, const QPointF &pt2)
{
    double offsetX = pt2.x() - pt1.x();
    double offsetY = pt2.y() - pt1.y();
    return qSqrt((offsetX * offsetX) + (offsetY * offsetY));
}

void CustomRocker::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    //绘制大圆
    painter.setPen(QPen(borderColor, borderWidth));
    painter.setBrush(bgColor);
    painter.drawEllipse(centerPoint.x() - radius, centerPoint.y() - radius, radius * 2, radius * 2);

    //绘制摇杆圆
    painter.setPen(Qt::NoPen);
    painter.setBrush(rockerColor);
    painter.drawEllipse(currentPoint.x() - rockerRadius, currentPoint.y() - rockerRadius, rockerRadius * 2, rockerRadius * 2);
}

void CustomRocker::resetPoint(const QPoint &point)
{
    QPoint tmp = point;
    double angle = 0.0;

    bool resetPos = online || qPow(tmp.x() - centerPoint.x(), 2.0) + qPow(tmp.y() - centerPoint.y(), 2.0) > qPow(radius, 2.0);
    {
        //     y
        //     ^
        //   2 | 1
        //-----------> x
        //   3 | 4

        //平行 于x 轴
        if (tmp.y() == centerPoint.y()) {
            if (tmp.x() > centerPoint.x()) { //右边
                angle = 0.0;
                if (resetPos) {
                    tmp.setX(centerPoint.x() + radius - 1);
                }
            } else {
                angle = 180.0;
                if (resetPos) {
                    tmp.setX(centerPoint.x() - radius + 1);
                }
            }
        }
        //平行 于y 轴
        else if (tmp.x() == centerPoint.x()) {
            if (tmp.y() > centerPoint.y()) { //下边
                angle = 270.0;
                if (resetPos) {
                    tmp.setY(centerPoint.y() + radius - 1);
                }
            } else {
                angle = 90.0;
                if (resetPos) {
                    tmp.setY(centerPoint.y() - radius + 1);
                }
            }
        }
        // 3\4 区域
        // 传统坐标 x→ y↑为正...显示器 x→ y↓为正  y相反
        else if (tmp.y() > centerPoint.y()) {
            double k = ((tmp.x() - centerPoint.x()) * 1.0) / (tmp.y() - centerPoint.y());
            angle = 90 - qAtan(k) / M_PI * 180;
            if (resetPos) {
                tmp.setX(centerPoint.x() + radius * qCos(angle * M_PI / 180));
                tmp.setY(centerPoint.y() + radius * qSin(angle * M_PI / 180));
            }
        }
        // 1\2 区域
        else if (tmp.y() < centerPoint.y()) {
            double k = ((tmp.x() - centerPoint.x()) * 1.0) / (centerPoint.y() - tmp.y());
            angle = qAtan(k) / M_PI * 180 - 90;
            if (resetPos) {
                tmp.setX(centerPoint.x() + radius * qCos(angle * M_PI / 180));
                tmp.setY(centerPoint.y() + radius * qSin(angle * M_PI / 180));
            }
        }

        if (angle < 0) {
            angle = qAbs(angle);
        } else {
            //要过滤掉正上方和正下方
            if (angle != 90 && angle != 270) {
                angle = 360.0 - angle;
            }
        }
    }

    currentPoint = tmp;
    emit moveAngle(angle, getDistance());
}

double CustomRocker::getDistance()
{
    return twoPtDistance(currentPoint, centerPoint);
}

bool CustomRocker::getOnline() const
{
    return this->online;
}

int CustomRocker::getBorderWidth() const
{
    return this->borderWidth;
}

int CustomRocker::getRockerRadius() const
{
    return this->rockerRadius;
}

QColor CustomRocker::getBorderColor() const
{
    return this->borderColor;
}

QColor CustomRocker::getBgColor() const
{
    return this->bgColor;
}

QColor CustomRocker::getRockerColor() const
{
    return this->rockerColor;
}

QSize CustomRocker::sizeHint() const
{
    return QSize(300, 300);
}

QSize CustomRocker::minimumSizeHint() const
{
    return QSize(20, 20);
}

void CustomRocker::setOnline(bool online)
{
    if (this->online != online) {
        this->online = online;
        this->update();
    }
}

void CustomRocker::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        this->update();
    }
}

void CustomRocker::setRockerRadius(int rockerRadius)
{
    if (this->rockerRadius != rockerRadius) {
        this->rockerRadius = rockerRadius;
        this->update();
    }
}

void CustomRocker::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        this->update();
    }
}

void CustomRocker::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

void CustomRocker::setRockerColor(const QColor &rockerColor)
{
    if (this->rockerColor != rockerColor) {
        this->rockerColor = rockerColor;
        this->update();
    }
}
