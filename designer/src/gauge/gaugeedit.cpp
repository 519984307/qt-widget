#pragma execution_character_set("utf-8")

#include "gaugeedit.h"
#include "qlineedit.h"
#include "qvalidator.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"

GaugeEdit::GaugeEdit(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    unit = "℃";

    startAngle = 60;
    endAngle = 60;
    animation = false;
    animationStep = 0.5;

    outerCircleColor = QColor(80, 80, 80);
    innerCircleColor = QColor(60, 60, 60);
    centerCircleColor = QColor(60, 60, 60);
    usedColor = QColor(24, 189, 155);
    freeColor = QColor(250, 250, 250);
    textColor = QColor(255, 255, 255);

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    offset = 0;
    lineEdit = new QLineEdit(this);
    //设置初始值
    lineEdit->setText("0");
    //设置居中对齐
    lineEdit->setAlignment(Qt::AlignCenter);
    //安装事件过滤器,识别焦点
    lineEdit->installEventFilter(this);

    //设置限制只能输入数字+小数位
    QString pattern = "^-?[0-9]+([.]{1}[0-9]+){0,1}$";
    //确切的说 QRegularExpression QRegularExpressionValidator 从5.0 5.1开始就有
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    QRegularExpression regExp(pattern);
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regExp, this);
#else
    QRegExp regExp(pattern);
    QRegExpValidator *validator = new QRegExpValidator(regExp, this);
#endif
    lineEdit->setValidator(validator);

    //关联信号槽
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    //设置样式表
    this->initStyle();
}

GaugeEdit::~GaugeEdit()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

bool GaugeEdit::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == lineEdit) {
        if (event->type() == QEvent::FocusIn) {
            //获取焦点扩大
            offset = 8;
            this->update();
        } else if (event->type() == QEvent::FocusOut) {
            //失去焦点恢复
            offset = 0;
            this->update();
        } else if (event->type() == QEvent::KeyPress) {
            //键盘按键直接修改值
            QKeyEvent *keyEvent = (QKeyEvent *)event;
            int keyValue = keyEvent->key();
            if (keyValue == Qt::Key_Up) {
                setValue(value + 1);
            } else if (keyValue == Qt::Key_Down) {
                setValue(value - 1);
            } else if (keyValue == Qt::Key_PageUp) {
                setValue(value + 10);
            } else if (keyValue == Qt::Key_PageDown) {
                setValue(value - 10);
            }
        } else if (event->type() == QEvent::Wheel) {
            //鼠标滚轮直接修改值
            QWheelEvent *whellEvent = (QWheelEvent *)event;
            //滚动的角度,*8就是鼠标滚动的距离
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
            int degrees = whellEvent->angleDelta().x() / 8;
#else
            int degrees = whellEvent->delta() / 8;
#endif
            //滚动的步数,*15就是鼠标滚动的角度
            int steps = degrees / 15;
            //将步数作为步长设置值
            setValue(value + steps);
        }
    }

    return QWidget::eventFilter(watched, event);
}

void GaugeEdit::resizeEvent(QResizeEvent *)
{
    lineEdit->resize(this->size());
    changeFont();
}

void GaugeEdit::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制外圆
    drawOuterCircle(&painter);
    //绘制内圆
    drawInnerCircle(&painter);
    //绘制当前进度
    drawProgress(&painter);
    //绘制中心圆
    drawCenterCircle(&painter);
    //绘制单位
    drawUnit(&painter);
}

void GaugeEdit::drawOuterCircle(QPainter *painter)
{
    int radius = 91 + offset;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(outerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeEdit::drawInnerCircle(QPainter *painter)
{
    int radius = 80 + offset;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(innerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeEdit::drawProgress(QPainter *painter)
{
    int radius = 75 + offset;
    painter->save();
    painter->setPen(Qt::NoPen);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0 - startAngle - endAngle;
    double angleCurrent = angleAll * ((currentValue - minValue) / (maxValue - minValue));
    double angleOther = angleAll - angleCurrent;

    //绘制当前值饼圆
    painter->setBrush(usedColor);
    painter->drawPie(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);

    //绘制剩余值饼圆
    painter->setBrush(freeColor);
    painter->drawPie(rect, (270 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void GaugeEdit::drawCenterCircle(QPainter *painter)
{
    int radius = 60 + offset;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(centerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeEdit::drawUnit(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(30);
    painter->setFont(font);

    int offsetY = 113;
    QRectF unitRect(-radius, -radius + offsetY, radius * 2, radius * 2 - offsetY);
    painter->drawText(unitRect, Qt::AlignCenter, unit);

    painter->restore();
}

void GaugeEdit::initStyle()
{
    QStringList qss;
    qss << "border:none;";
    qss << "background-color:rgba(0,0,0,0);";
    qss << "selection-background-color:rgba(0,0,0,0);";
    qss << QString("color:%1;").arg(textColor.name());
    lineEdit->setStyleSheet(qss.join(""));
}

void GaugeEdit::changeFont()
{
    QString text = QString::number(value);
    bool point = text.contains(".");
    float len = text.length();
    len = (point ? len - 1 : len);
    float fontWidth = qMin(lineEdit->width(), lineEdit->height()) * 0.65;

    float fontSize;
    if (len == 1) {
        fontSize = fontWidth * 0.6;
    } else if (len == 2) {
        fontSize = fontWidth * 0.5;
    } else if (len == 3) {
        fontSize = fontWidth * 0.4;
    } else if (len == 4) {
        fontSize = fontWidth * 0.35;
    } else if (len == 5) {
        fontSize = fontWidth * 0.3;
    } else if (len == 6) {
        fontSize = fontWidth * 0.25;
    } else if (len == 7) {
        fontSize = fontWidth * 0.2;
    } else if (len == 8) {
        fontSize = fontWidth * 0.15;
    } else {
        return;
    }

    fontSize = (point ? fontSize * 0.9 : fontSize);
    QFont font;
    font.setPixelSize(fontSize);
    lineEdit->setFont(font);
}

void GaugeEdit::updateValue()
{
    if (!reverse) {
        if (currentValue >= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue += animationStep;
        }
    } else {
        if (currentValue <= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue -= animationStep;
        }
    }

    this->update();
}

void GaugeEdit::textChanged(const QString &value)
{
    setValue(value.toDouble());
    changeFont();
}

double GaugeEdit::getMinValue() const
{
    return this->minValue;
}

double GaugeEdit::getMaxValue() const
{
    return this->maxValue;
}

double GaugeEdit::getValue() const
{
    return this->value;
}

QString GaugeEdit::getUnit() const
{
    return this->unit;
}

int GaugeEdit::getStartAngle() const
{
    return this->startAngle;
}

int GaugeEdit::getEndAngle() const
{
    return this->endAngle;
}

bool GaugeEdit::getAnimation() const
{
    return this->animation;
}

double GaugeEdit::getAnimationStep() const
{
    return this->animationStep;
}

QColor GaugeEdit::getOuterCircleColor() const
{
    return this->outerCircleColor;
}

QColor GaugeEdit::getInnerCircleColor() const
{
    return this->innerCircleColor;
}

QColor GaugeEdit::getCenterCircleColor() const
{
    return this->centerCircleColor;
}

QColor GaugeEdit::getUsedColor() const
{
    return this->usedColor;
}

QColor GaugeEdit::getFreeColor() const
{
    return this->freeColor;
}

QColor GaugeEdit::getTextColor() const
{
    return this->textColor;
}

QSize GaugeEdit::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeEdit::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeEdit::setRange(double minValue, double maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        setValue(minValue);
    } else if (value > maxValue) {
        setValue(maxValue);
    }

    this->update();
}

void GaugeEdit::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeEdit::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeEdit::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeEdit::setValue(double value)
{
    //值和当前值一致则无需处理
    if (value == this->value) {
        return;
    }

    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        value = minValue;
    } else if (value > maxValue) {
        value = maxValue;
    }

    if (value > this->value) {
        reverse = false;
    } else if (value < this->value) {
        reverse = true;
    }

    this->value = value;
    emit valueChanged(value);
    emit valueChanged((int)value);

    if (!animation) {
        currentValue = this->value;
        this->update();
    } else {
        timer->start();
    }

    lineEdit->setText(QString::number(value));
}

void GaugeEdit::setValue(int value)
{
    setValue((double)value);
}

void GaugeEdit::setUnit(const QString &unit)
{
    if (this->unit != unit) {
        this->unit = unit;
        this->update();
    }
}

void GaugeEdit::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        this->update();
    }
}

void GaugeEdit::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        this->update();
    }
}

void GaugeEdit::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        this->update();
    }
}

void GaugeEdit::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        this->update();
    }
}

void GaugeEdit::setOuterCircleColor(const QColor &outerCircleColor)
{
    if (this->outerCircleColor != outerCircleColor) {
        this->outerCircleColor = outerCircleColor;
        this->update();
    }
}

void GaugeEdit::setInnerCircleColor(const QColor &innerCircleColor)
{
    if (this->innerCircleColor != innerCircleColor) {
        this->innerCircleColor = innerCircleColor;
        this->update();
    }
}

void GaugeEdit::setCenterCircleColor(const QColor &centerCircleColor)
{
    if (this->centerCircleColor != centerCircleColor) {
        this->centerCircleColor = centerCircleColor;
        this->update();
    }
}

void GaugeEdit::setUsedColor(const QColor &usedColor)
{
    if (this->usedColor != usedColor) {
        this->usedColor = usedColor;
        this->update();
    }
}

void GaugeEdit::setFreeColor(const QColor &freeColor)
{
    if (this->freeColor != freeColor) {
        this->freeColor = freeColor;
        this->update();
    }
}

void GaugeEdit::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
        this->initStyle();
    }
}
