#pragma execution_character_set("utf-8")

#include "scantantan.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "qevent.h"
#include "qtimer.h"
#include "qmath.h"
#include "qpropertyanimation.h"
#include "qsequentialanimationgroup.h"
#include "qdebug.h"

ScanTanTan::ScanTanTan(QWidget *parent) : QWidget(parent)
{
    image = QPixmap(":/image/head.jpg");
    imageBorderWidth = 5;
    imageBorderColor = QColor(255, 255, 255);

    scanRadius = 98;
    scanWidth = 2;
    ringWidth = 5;

    scanStep = 2;
    ringStep = 2;

    ringColor = QColor(255, 0, 0);
    scanColor = QColor(255, 0, 0);

    isPressed = false;
    ringRadius = 50;
    imageRadius = 40;
    scanDeg = 0;

    //定时器绘制扫描圈+扩散圈
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(changeScan()));
    connect(timer, SIGNAL(timeout()), this, SLOT(changeRing()));
    timer->start(15);

    //动画改变中间图片的大小,先从小到大,然后从大到小,最后从小到正常
    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "");
    connect(animation1, SIGNAL(valueChanged(QVariant)), this, SLOT(updateImage(QVariant)));
    animation1->setStartValue(40);
    animation1->setEndValue(50);
    animation1->setDuration(300);

    QPropertyAnimation *animation2 = new QPropertyAnimation(this, "");
    connect(animation2, SIGNAL(valueChanged(QVariant)), this, SLOT(updateImage(QVariant)));
    animation2->setStartValue(50);
    animation2->setEndValue(30);
    animation2->setDuration(300);

    QPropertyAnimation *animation3 = new QPropertyAnimation(this, "");
    connect(animation3, SIGNAL(valueChanged(QVariant)), this, SLOT(updateImage(QVariant)));
    animation3->setStartValue(30);
    animation3->setEndValue(40);
    animation3->setDuration(300);

    //将动画加入动画序列,序列按照顺序执行
    animationGroup = new QSequentialAnimationGroup() ;
    animationGroup->addAnimation(animation1);
    animationGroup->addAnimation(animation2);
    animationGroup->addAnimation(animation3);
}

void ScanTanTan::mousePressEvent(QMouseEvent *event)
{
    //鼠标按下,判断按下出和圆中心的距离是否是扩散圈的起始半径内
    if (!isPressed) {
        QPointF pressedPoint = event->pos();
        QPointF centerPoint = rect().center();
        int offset = twoPtDistance(pressedPoint, centerPoint);
        if (offset <= ringRadius) {
            isPressed = true;
            animationGroup->stop();
            this->update();
        }
    }
}

void ScanTanTan::mouseReleaseEvent(QMouseEvent *)
{
    //鼠标松开的时候创建一个扩散圈加入队列
    if (isPressed) {
        struct RingData ring;
        ring.radius = ringRadius;
        ring.width = ringWidth;
        ring.alpha = 255;
        rings.append(ring);

        isPressed = false;
        animationGroup->start();
        this->update();
    }
}

void ScanTanTan::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制扫描线
    drawScan(&painter);
    //绘制扩散圈
    drawRing(&painter);
    //绘制中间图片
    drawImage(&painter);
}

void ScanTanTan::drawScan(QPainter *painter)
{
    painter->save();

    //锥形渐变颜色,通过透明度控制形成扫描效果
    QConicalGradient conicalGradient(0, 0, scanDeg);
    QColor color = scanColor;
    color.setAlpha(50);
    conicalGradient.setColorAt(0, color);
    color.setAlpha(0);
    conicalGradient.setColorAt(1, color);

    //设置画笔画刷
    QPen pen;
    pen.setWidth(scanWidth);
    pen.setBrush(conicalGradient);
    painter->setPen(pen);
    painter->setBrush(conicalGradient);

    //绘制饼圆
    QRect rect(-scanRadius, -scanRadius, scanRadius * 2, scanRadius * 2);
    painter->drawPie(rect, scanDeg * 16, 360 * 16);

    painter->restore();
}

void ScanTanTan::drawRing(QPainter *painter)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);

    //绘制所有扩散圈,扩散圈其实就是个没有背景颜色的圆形
    for (int i = 0; i < rings.count(); i++) {
        RingData ring = rings.at(i);
        int radius = ring.radius;
        float width = ring.width;
        int alpha = 255 - ring.alpha;
        QColor color = ringColor;
        color.setAlpha(alpha);

        QPen pen;
        pen.setWidthF(width);
        pen.setColor(color);
        painter->setPen(pen);
        painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    }

    painter->restore();
}

void ScanTanTan::drawImage(QPainter *painter)
{
    painter->save();

    //设置圆形遮罩路径,产生圆形头像效果
    QPainterPath path;
    path.addEllipse(QPoint(0, 0), imageRadius, imageRadius);
    painter->setClipPath(path);

    //绘制图片
    QRect rect(-imageRadius, -imageRadius, imageRadius * 2, imageRadius * 2);
    painter->drawPixmap(rect, image);

    //绘制图片边缘圆形
    QPen pen;
    pen.setWidth(imageBorderWidth);
    pen.setColor(imageBorderColor);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

    //以下两种方法二选一,其实绘制360度的圆弧=绘制无背景的圆形
    //painter->drawArc(rect, 0, 360 * 16);
    painter->drawEllipse(rect);

    painter->restore();
}

void ScanTanTan::changeScan()
{
    //改变角度,产生扫描效果
    scanDeg = scanDeg - scanStep;
    if (scanDeg <= 0) {
        scanDeg = 360;
    }

    this->update();
}

void ScanTanTan::changeRing()
{
    //逐个改变扩散圈的半径+边框宽度+透明度,当达到扫描圈的半径则移除消失
    for (int i = 0; i < rings.count(); i++) {
        RingData ring = rings.at(i);
        if (ring.radius < scanRadius) {
            ring.radius = ring.radius + ringStep;
            ring.width = ringWidth - ring.radius * ((float)ringWidth / scanRadius);
            ring.alpha = ring.radius * (255 / scanRadius);
            rings[i] = ring;
        } else {
            rings.removeAt(i);
        }
    }
}

void ScanTanTan::updateImage(const QVariant &value)
{
    //必须限定在可见状态,不然默认初始化的时候会执行导致imageRadius值不对
    if (this->isVisible()) {
        imageRadius = value.toInt();
        this->update();
    }
}

double ScanTanTan::twoPtDistance(const QPointF &pt1, const QPointF &pt2)
{
    double offsetX = pt2.x() - pt1.x();
    double offsetY = pt2.y() - pt1.y();
    return qSqrt((offsetX * offsetX) + (offsetY * offsetY));
}

QPixmap ScanTanTan::getImage() const
{
    return this->image;
}

int ScanTanTan::getImageBorderWidth() const
{
    return this->imageBorderWidth;
}

QColor ScanTanTan::getImageBorderColor() const
{
    return this->imageBorderColor;
}

int ScanTanTan::getScanRadius() const
{
    return this->scanRadius;
}

int ScanTanTan::getScanWidth() const
{
    return this->scanWidth;
}

int ScanTanTan::getRingWidth() const
{
    return this->ringWidth;
}

int ScanTanTan::getScanStep() const
{
    return this->scanStep;
}

int ScanTanTan::getRingStep() const
{
    return this->ringStep;
}

QColor ScanTanTan::getScanColor() const
{
    return this->scanColor;
}

QColor ScanTanTan::getRingColor() const
{
    return this->ringColor;
}

QSize ScanTanTan::sizeHint() const
{
    return QSize(200, 200);
}

QSize ScanTanTan::minimumSizeHint() const
{
    return QSize(50, 50);
}

void ScanTanTan::setImage(const QPixmap &image)
{
    if (!image.isNull()) {
        this->image = image;
        this->update();
    }
}

void ScanTanTan::setImageBorderWidth(int imageBorderWidth)
{
    if (this->imageBorderWidth != imageBorderWidth) {
        this->imageBorderWidth = imageBorderWidth;
        this->update();
    }
}

void ScanTanTan::setImageBorderColor(const QColor &imageBorderColor)
{
    if (this->imageBorderColor != imageBorderColor) {
        this->imageBorderColor = imageBorderColor;
        this->update();
    }
}

void ScanTanTan::setScanRadius(int scanRadius)
{
    if (this->scanRadius != scanRadius) {
        this->scanRadius = scanRadius;
        this->update();
    }
}

void ScanTanTan::setScanWidth(int scanWidth)
{
    if (this->scanWidth != scanWidth) {
        this->scanWidth = scanWidth;
        this->update();
    }
}

void ScanTanTan::setRingWidth(int ringWidth)
{
    if (this->ringWidth != ringWidth) {
        this->ringWidth = ringWidth;
        this->update();
    }
}

void ScanTanTan::setScanStep(int scanStep)
{
    if (this->scanStep != scanStep) {
        this->scanStep = scanStep;
        this->update();
    }
}

void ScanTanTan::setRingStep(int ringStep)
{
    if (this->ringStep != ringStep) {
        this->ringStep = ringStep;
        this->update();
    }
}

void ScanTanTan::setScanColor(const QColor &scanColor)
{
    if (this->scanColor != scanColor) {
        this->scanColor = scanColor;
        this->update();
    }
}

void ScanTanTan::setRingColor(const QColor &ringColor)
{
    if (this->ringColor != ringColor) {
        this->ringColor = ringColor;
        this->update();
    }
}
