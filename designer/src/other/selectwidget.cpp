#pragma execution_character_set("utf-8")

#include "selectwidget.h"
#include "qpainter.h"
#include "qevent.h"
#include "qdebug.h"

SelectWidget::SelectWidget(QWidget *parent) : QWidget(parent)
{
    drawPoint = false;
    padding = 5;
    borderWidth = 1;
    pointSize = 8;
    pointColor = QColor(34, 163, 168);
    pointStyle = PointStyle_Rect;

    mousePressed = false;
    mousePoint = QPoint(0, 0);
    mouseRect = QRect(0, 0, 0, 0);

    for (int i = 0; i < 8; ++i) {
        pressedArea << false;
        pressedRect << QRect(0, 0, 0, 0);
    }

    widget = 0;

    //设置鼠标追踪为真,并绑定事件过滤器,可以获取焦点用于按键移动位置
    this->setMouseTracking(true);
    //安装事件过滤器,识别鼠标拖动和拉伸大小
    this->installEventFilter(this);
    //设置焦点策略,以便鼠标按下获取焦点并手柄可见
    this->setFocusPolicy(Qt::StrongFocus);
}

bool SelectWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == widget) {
        if (event->type() == QEvent::Resize) {
            //设置当前窗体大小为跟随窗体的大小增加部分
            this->resize(widget->size() + QSize(padding * 2, padding * 2));
        } else if (event->type() == QEvent::Move) {
            //将当前窗体移到偏移位置
            this->move(widget->pos() - QPoint(padding, padding));
        }
    } else if (watched == this) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Left) {
                this->move(this->pos() - QPoint(1, 0));
            } else if (keyEvent->key() == Qt::Key_Right) {
                this->move(this->pos() + QPoint(1, 0));
            } else if (keyEvent->key() == Qt::Key_Up) {
                this->move(this->pos() - QPoint(0, 1));
            } else if (keyEvent->key() == Qt::Key_Down) {
                this->move(this->pos() + QPoint(0, 1));
            } else if (keyEvent->key() == Qt::Key_Delete) {
                emit widgetDelete(widget);
                widget->deleteLater();
                this->deleteLater();
                widget = 0;
            }

            //重新设置附带窗体的位置和大小
            if (widget != 0) {
                widget->setGeometry(this->x() + padding, this->y() + padding, this->width() - padding * 2, this->height() - padding * 2);
            }

            return QWidget::eventFilter(watched, event);
        } else if (event->type() == QEvent::Resize) {
            //重新计算八个描点的区域,描点区域的作用还有就是计算鼠标坐标是否在某一个区域内
            int width = this->width();
            int height = this->height();

            //左侧描点区域
            pressedRect[0] = QRectF(0, height / 2 - pointSize / 2, pointSize, pointSize);
            //右侧描点区域
            pressedRect[1] = QRectF(width - pointSize, height / 2 - pointSize / 2, pointSize, pointSize);
            //上侧描点区域
            pressedRect[2] = QRectF(width / 2 - pointSize / 2, 0, pointSize, pointSize);
            //下侧描点区域
            pressedRect[3] = QRectF(width / 2 - pointSize / 2, height - pointSize, pointSize, pointSize);

            //左上角描点区域
            pressedRect[4] = QRectF(0, 0, pointSize, pointSize);
            //右上角描点区域
            pressedRect[5] = QRectF(width - pointSize, 0, pointSize, pointSize);
            //左下角描点区域
            pressedRect[6] = QRectF(0, height - pointSize, pointSize, pointSize);
            //右下角描点区域
            pressedRect[7] = QRectF(width - pointSize, height - pointSize, pointSize, pointSize);
        } else if (event->type() == QEvent::MouseButtonPress) {
            //记住鼠标按下的坐标+窗体区域
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            mousePoint = mouseEvent->pos();
            mouseRect = this->geometry();

            //判断按下的手柄的区域位置
            if (pressedRect.at(0).contains(mousePoint)) {
                pressedArea[0] = true;
            } else if (pressedRect.at(1).contains(mousePoint)) {
                pressedArea[1] = true;
            } else if (pressedRect.at(2).contains(mousePoint)) {
                pressedArea[2] = true;
            } else if (pressedRect.at(3).contains(mousePoint)) {
                pressedArea[3] = true;
            } else if (pressedRect.at(4).contains(mousePoint)) {
                pressedArea[4] = true;
            } else if (pressedRect.at(5).contains(mousePoint)) {
                pressedArea[5] = true;
            } else if (pressedRect.at(6).contains(mousePoint)) {
                pressedArea[6] = true;
            } else if (pressedRect.at(7).contains(mousePoint)) {
                pressedArea[7] = true;
            } else {
                mousePressed = true;
            }

            if (widget != 0) {
                emit widgetPressed(widget);
            }
        } else if (event->type() == QEvent::MouseMove) {
            //设置对应鼠标形状
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            QPoint point = mouseEvent->pos();
            if (pressedRect.at(0).contains(point)) {
                this->setCursor(Qt::SizeHorCursor);
            } else if (pressedRect.at(1).contains(point)) {
                this->setCursor(Qt::SizeHorCursor);
            } else if (pressedRect.at(2).contains(point)) {
                this->setCursor(Qt::SizeVerCursor);
            } else if (pressedRect.at(3).contains(point)) {
                this->setCursor(Qt::SizeVerCursor);
            } else if (pressedRect.at(4).contains(point)) {
                this->setCursor(Qt::SizeFDiagCursor);
            } else if (pressedRect.at(5).contains(point)) {
                this->setCursor(Qt::SizeBDiagCursor);
            } else if (pressedRect.at(6).contains(point)) {
                this->setCursor(Qt::SizeBDiagCursor);
            } else if (pressedRect.at(7).contains(point)) {
                this->setCursor(Qt::SizeFDiagCursor);
            } else {
                this->setCursor(Qt::ArrowCursor);
            }

            //根据当前鼠标位置,计算XY轴移动了多少
            int dx = point.x() - mousePoint.x();
            int dy = point.y() - mousePoint.y();

            int rectX = mouseRect.x();
            int rectY = mouseRect.y();
            int rectW = mouseRect.width();
            int rectH = mouseRect.height();

            //根据按下处的位置判断是否是移动控件还是拉伸控件
            if (mousePressed) {
                this->move(this->x() + dx, this->y() + dy);
            } else if (pressedArea.at(0)) {
                int resizeW = this->width() - dx;
                if (this->minimumWidth() <= resizeW) {
                    this->setGeometry(this->x() + dx, rectY, resizeW, rectH);
                }
            } else if (pressedArea.at(1)) {
                this->setGeometry(rectX, rectY, rectW + dx, rectH);
            } else if (pressedArea.at(2)) {
                int resizeH = this->height() - dy;
                if (this->minimumHeight() <= resizeH) {
                    this->setGeometry(rectX, this->y() + dy, rectW, resizeH);
                }
            } else if (pressedArea.at(3)) {
                this->setGeometry(rectX, rectY, rectW, rectH + dy);
            } else if (pressedArea.at(4)) {
                int resizeW = this->width() - dx;
                int resizeH = this->height() - dy;
                if (this->minimumWidth() <= resizeW) {
                    this->setGeometry(this->x() + dx, this->y(), resizeW, resizeH);
                }
                if (this->minimumHeight() <= resizeH) {
                    this->setGeometry(this->x(), this->y() + dy, resizeW, resizeH);
                }
            } else if (pressedArea.at(5)) {
                int resizeW = rectW + dx;
                int resizeH = this->height() - dy;
                if (this->minimumHeight() <= resizeH) {
                    this->setGeometry(this->x(), this->y() + dy, resizeW, resizeH);
                }
            } else if (pressedArea.at(6)) {
                int resizeW = this->width() - dx;
                int resizeH = rectH + dy;
                if (this->minimumWidth() <= resizeW) {
                    this->setGeometry(this->x() + dx, this->y(), resizeW, resizeH);
                }
                if (this->minimumHeight() <= resizeH) {
                    this->setGeometry(this->x(), this->y(), resizeW, resizeH);
                }
            } else if (pressedArea.at(7)) {
                int resizeW = rectW + dx;
                int resizeH = rectH + dy;
                this->setGeometry(this->x(), this->y(), resizeW, resizeH);
            }

            //重新设置附带窗体的位置和大小
            if (widget != 0) {
                widget->setGeometry(this->x() + padding, this->y() + padding, this->width() - padding * 2, this->height() - padding * 2);
            }
        } else if (event->type() == QEvent::MouseButtonRelease) {
            mousePressed = false;
            for (int i = 0; i < 8; ++i) {
                pressedArea[i] = false;
            }

            if (widget != 0) {
                emit widgetRelease(widget);
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

void SelectWidget::paintEvent(QPaintEvent *)
{
    if (!drawPoint) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(pointColor);

    if (pointStyle == PointStyle_Rect) {
        drawRect(&painter);
    } else if (pointStyle == PointStyle_Circle) {
        drawCircle(&painter);
    }

    if (borderWidth > 0) {
        drawBorder(&painter);
    }
}

void SelectWidget::drawRect(QPainter *painter)
{
    //逐个绘制 左上角点+顶边中间点+右上角点+左边中间点+右边中间点+左下角点+底边中间点+右下角点
    painter->save();
    for (int i = 0; i < 8; ++i) {
        painter->drawRect(pressedRect.at(i));
    }
    painter->restore();
}

void SelectWidget::drawCircle(QPainter *painter)
{
    //逐个绘制 左上角点+顶边中间点+右上角点+左边中间点+右边中间点+左下角点+底边中间点+右下角点
    painter->save();
    for (int i = 0; i < 8; ++i) {
        painter->drawEllipse(pressedRect.at(i));
    }
    painter->restore();
}

void SelectWidget::drawBorder(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setWidth(borderWidth);
    pen.setColor(pointColor);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    QRectF borderRect(pointSize / 2, pointSize / 2, width() - pointSize, height() - pointSize);
    painter->drawRect(borderRect);
    painter->restore();
}

bool SelectWidget::getDrawPoint() const
{
    return this->drawPoint;
}

int SelectWidget::getPadding() const
{
    return this->padding;
}

int SelectWidget::getBorderWidth() const
{
    return this->borderWidth;
}

int SelectWidget::getPointSize() const
{
    return this->pointSize;
}

QColor SelectWidget::getPointColor() const
{
    return this->pointColor;
}

SelectWidget::PointStyle SelectWidget::getPointStyle() const
{
    return this->pointStyle;
}

QWidget *SelectWidget::getWidget() const
{
    return widget;
}

QSize SelectWidget::sizeHint() const
{
    return QSize(200, 200);
}

QSize SelectWidget::minimumSizeHint() const
{
    return QSize(30, 30);
}

void SelectWidget::setDrawPoint(bool drawPoint)
{
    if (this->drawPoint != drawPoint) {
        this->drawPoint = drawPoint;
        this->update();
    }
}

void SelectWidget::setPadding(int padding)
{
    if (this->padding != padding) {
        this->padding = padding;
        this->update();
    }
}

void SelectWidget::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        this->update();
    }
}

void SelectWidget::setPointSize(int pointSize)
{
    if (this->pointSize != pointSize) {
        this->pointSize = pointSize;
        this->update();
    }
}

void SelectWidget::setPointColor(const QColor &pointColor)
{
    if (this->pointColor != pointColor) {
        this->pointColor = pointColor;
        this->update();
    }
}

void SelectWidget::setPointStyle(const SelectWidget::PointStyle &pointStyle)
{
    if (this->pointStyle != pointStyle) {
        this->pointStyle = pointStyle;
        this->update();
    }
}

void SelectWidget::setWidget(QWidget *widget)
{
    //绑定事件过滤器,响应 geometry 变化
    widget->installEventFilter(this);

    this->widget = widget;
    this->widget->setVisible(true);
    this->setVisible(true);

    //设置最小尺寸
    this->setMinimumSize(30, 30);
    //设置当前窗体大小为跟随窗体的大小增加部分
    this->resize(this->widget->size() + QSize(padding * 2, padding * 2));
    //将当前窗体移到偏移位置
    this->move(this->widget->pos() - QPoint(padding, padding));
}
