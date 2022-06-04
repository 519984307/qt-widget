#pragma execution_character_set("utf-8")

#include "shadowwidget.h"
#include "qgraphicseffect.h"
#include "qpainter.h"
#include "qdebug.h"

ShadowWidget::ShadowWidget(QWidget *parent) : QWidget(parent)
{
    borderRadius = 5;
    borderMargin = 10;

    triangleWidth = 12;
    triangleHeight = 12;

    borderColor = QColor(214, 77, 84);
    bgColor = QColor(249, 249, 249);

    blurRadius = 20;
    triangleRatio = 0.5;
    trianglePosition = TrianglePosition_Top;

    //设置背景透明+无边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::FramelessWindowHint);

    //设置阴影
    shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor(borderColor);
    shadowEffect->setBlurRadius(blurRadius);
    this->setGraphicsEffect(shadowEffect);
}

void ShadowWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    drawPath();
    painter.drawPath(path);
}

void ShadowWidget::drawPath()
{
    int w = this->width();
    int h = this->height();

    //弧形宽高一样
    const int arc_w = borderRadius * 2;
    const int arc_h = arc_w;

    //4个圆角坐标
    int arc_x1, arc_y1; //右上角
    int arc_x2, arc_y2; //右下角
    int arc_x3, arc_y3; //左下角
    int arc_x4, arc_y4; //左上角

    //从左到右 从上到下
    int tri_x1, tri_y1;
    int tri_x2, tri_y2;
    int tri_x3, tri_y3;

    switch (trianglePosition) {
        case ShadowWidget::TrianglePosition_Top: {
            arc_x1 = w - borderMargin - borderRadius;
            arc_y1 = triangleHeight + borderMargin + borderRadius;

            arc_x2 = w - borderMargin - borderRadius;
            arc_y2 = h - borderMargin - borderRadius;

            arc_x3 = borderMargin + borderRadius;
            arc_y3 = h - borderMargin - borderRadius;

            arc_x4 = borderMargin + borderRadius;
            arc_y4 = borderMargin + borderRadius + triangleHeight;

            const int w2 = w - borderMargin * 2 - borderRadius * 2 - triangleWidth;
            tri_x1 = borderRadius + borderMargin + w2 * triangleRatio;
            tri_y1 = triangleHeight + borderMargin;

            tri_x2 = tri_x1 + triangleWidth / 2;
            tri_y2 = borderMargin;

            tri_x3 = tri_x1 + triangleWidth;
            tri_y3 = tri_y1;
            break;
        }
        case ShadowWidget::TrianglePosition_Right: {
            arc_x1 = w - borderMargin - borderRadius - triangleWidth;
            arc_y1 = borderMargin + borderRadius;

            arc_x2 = w - borderMargin - borderRadius - triangleWidth;
            arc_y2 = h - borderMargin - borderRadius;

            arc_x3 = borderMargin + borderRadius;
            arc_y3 = h - borderMargin - borderRadius;

            arc_x4 = borderMargin + borderRadius;
            arc_y4 = borderMargin + borderRadius;

            const int h2 = h - borderMargin * 2 - borderRadius * 2 - triangleHeight;
            tri_x1 = w - borderMargin - triangleWidth;
            tri_y1 = borderRadius + borderMargin + h2 * triangleRatio;

            tri_x2 = w - borderMargin;
            tri_y2 = tri_y1 + triangleHeight / 2;

            tri_x3 = tri_x1;
            tri_y3 = tri_y1 + triangleHeight;
            break;
        }
        case ShadowWidget::TrianglePosition_Bottom: {
            arc_x1 = w - borderMargin - borderRadius;
            arc_y1 = borderMargin + borderRadius;

            arc_x2 = w - borderMargin - borderRadius;
            arc_y2 = h - borderMargin - borderRadius - triangleHeight;

            arc_x3 = borderMargin + borderRadius;
            arc_y3 = h - borderMargin - borderRadius - triangleHeight;

            arc_x4 = borderMargin + borderRadius;
            arc_y4 = borderMargin + borderRadius;

            const int w2 = w - borderMargin * 2 - borderRadius * 2 - triangleWidth;
            tri_x1 = borderRadius + borderMargin + w2 * triangleRatio;
            tri_y1 = h - triangleHeight - borderMargin;

            tri_x2 = tri_x1 + triangleWidth / 2;
            tri_y2 = h - borderMargin;

            tri_x3 = tri_x1 + triangleWidth;
            tri_y3 = tri_y1;
            break;
        }
        case ShadowWidget::TrianglePosition_Left: {
            arc_x1 = w - borderMargin - borderRadius;
            arc_y1 = borderMargin + borderRadius;

            arc_x2 = w - borderMargin - borderRadius;
            arc_y2 = h - borderMargin - borderRadius;

            arc_x3 = borderMargin + borderRadius + triangleWidth;
            arc_y3 = h - borderMargin - borderRadius;

            arc_x4 = borderMargin + borderRadius + triangleWidth;
            arc_y4 = borderMargin + borderRadius;

            const int h2 = h - borderMargin * 2 - borderRadius * 2 - triangleHeight;
            tri_x1 = borderMargin + triangleWidth;
            tri_y1 = borderRadius + borderMargin + h2 * triangleRatio;

            tri_x2 = borderMargin;
            tri_y2 = tri_y1 + triangleHeight / 2;

            tri_x3 = tri_x1;
            tri_y3 = tri_y1 + triangleHeight;
            break;
        }
        default: {
            arc_x1 = w - borderMargin - borderRadius;
            arc_y1 = borderMargin + borderRadius;

            arc_x2 = w - borderMargin - borderRadius;
            arc_y2 = h - borderMargin - borderRadius;

            arc_x3 = borderMargin + borderRadius;
            arc_y3 = h - borderMargin - borderRadius;

            arc_x4 = borderMargin + borderRadius;
            arc_y4 = borderMargin + borderRadius;
            break;
        }
    }

    //三角形路径
    QPainterPath path;
    if (trianglePosition != ShadowWidget::TrianglePosition_None) {
        path.moveTo(tri_x1, tri_y1);
        path.lineTo(tri_x2, tri_y2);
        path.lineTo(tri_x3, tri_y3);
    }

    //3个矩形边缘 中间上下+左侧+右侧
    path.addRect(arc_x4, arc_y4 - borderRadius, arc_x1 - arc_x4, arc_y3 - arc_y4 + borderRadius * 2);
    path.addRect(arc_x4 - borderRadius, arc_y4, borderRadius, arc_y3 - arc_y4);
    path.addRect(arc_x1, arc_y1, borderRadius, arc_y2 - arc_y1);

    //添加 4个 1/4 圆
    path.moveTo(arc_x1, arc_y1);
    path.arcTo(QRectF(arc_x1 - borderRadius, arc_y1 - borderRadius, arc_w, arc_h), 0, 90);

    path.moveTo(arc_x2, arc_y2);
    path.arcTo(QRectF(arc_x2 - borderRadius, arc_y2 - borderRadius, arc_w, arc_h), 270, 90);

    path.moveTo(arc_x3, arc_y3);
    path.arcTo(QRectF(arc_x3 - borderRadius, arc_y3 - borderRadius, arc_w, arc_h), 180, 90);

    path.moveTo(arc_x4, arc_y4);
    path.arcTo(QRectF(arc_x4 - borderRadius, arc_y4 - borderRadius, arc_w, arc_h), 90, 90);

    this->path = path;
}

int ShadowWidget::getBorderRadius() const
{
    return this->borderRadius;
}

int ShadowWidget::getBorderMargin() const
{
    return this->borderMargin;
}

int ShadowWidget::getTriangleWidth() const
{
    return this->triangleWidth;
}

int ShadowWidget::getTriangleHeight() const
{
    return this->triangleHeight;
}

QColor ShadowWidget::getBorderColor() const
{
    return this->borderColor;
}

QColor ShadowWidget::getBgColor() const
{
    return this->bgColor;
}

double ShadowWidget::getBlurRadius() const
{
    return this->blurRadius;
}

double ShadowWidget::getTriangleRatio() const
{
    return this->triangleRatio;
}

ShadowWidget::TrianglePosition ShadowWidget::getTrianglePosition() const
{
    return this->trianglePosition;
}

QSize ShadowWidget::sizeHint() const
{
    return QSize(400, 300);
}

QSize ShadowWidget::minimumSizeHint() const
{
    return QSize(40, 30);
}

void ShadowWidget::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        this->update();
    }
}

void ShadowWidget::setBorderMargin(int borderMargin)
{
    if (this->borderMargin != borderMargin) {
        this->borderMargin = borderMargin;
        this->update();
    }
}

void ShadowWidget::setTriangleWidth(int triangleWidth)
{
    if (this->triangleWidth != triangleWidth) {
        this->triangleWidth = triangleWidth;
        this->update();
    }
}

void ShadowWidget::setTriangleHeight(int triangleHeight)
{
    if (this->triangleHeight != triangleHeight) {
        this->triangleHeight = triangleHeight;
        this->update();
    }
}

void ShadowWidget::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        shadowEffect->setColor(borderColor);
    }
}

void ShadowWidget::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

void ShadowWidget::setBlurRadius(double blurRadius)
{
    if (this->blurRadius != blurRadius) {
        this->blurRadius = blurRadius;
        shadowEffect->setBlurRadius(blurRadius);
    }
}

void ShadowWidget::setTriangleRatio(double triangleRatio)
{
    if (this->triangleRatio != triangleRatio) {
        this->triangleRatio = triangleRatio;
        this->update();
    }
}

void ShadowWidget::setTrianglePosition(const ShadowWidget::TrianglePosition &trianglePosition)
{
    if (this->trianglePosition != trianglePosition) {
        this->trianglePosition = trianglePosition;
        this->update();
    }
}
