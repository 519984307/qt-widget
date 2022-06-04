#pragma execution_character_set("utf-8")

#include "xstackwidget.h"
#include "qpropertyanimation.h"
#include "qdebug.h"

XStackWidget::XStackWidget(QWidget *parent) : QWidget(parent)
{
    duration = 500;
    offset = 0;
    currentIndex = 0;
    lastIndex = 0;

    //实例化动画对象
    animation = new QPropertyAnimation(this, "");
    animation->setDuration(duration);
    connect(animation, SIGNAL(valueChanged(QVariant)), this, SLOT(onValueChanged(QVariant)));
    connect(animation, SIGNAL(finished()), this, SLOT(onMoveFinished()));
}

XStackWidget::~XStackWidget()
{
    animation->stop();
}

void XStackWidget::resizeEvent(QResizeEvent *)
{
    int size = widgetCount();
    if (size <= 0) {
        return;
    }

    for (int i = 0; i < size; i++) {
        listWidget.at(i)->resize(this->width(), this->height());
    }

    if (animation->state() == QAbstractAnimation::Running) {
        moveAnimationStart();
    } else {
        setWidgetsVisible();
        onValueChanged(0);
    }
}

QSize XStackWidget::sizeHint() const
{
    return QSize(300, 300);
}

QSize XStackWidget::minimumSizeHint() const
{
    return QSize(30, 30);
}

int XStackWidget::widgetCount() const
{
    return listWidget.size();
}

int XStackWidget::widgetIndex() const
{
    return currentIndex;
}

void XStackWidget::setDuration(int duration)
{
    this->duration = duration;
}

int XStackWidget::addWidget(QWidget *widget)
{
    //防止重复插入窗体
    int index = indexOf(widget);
    if (index >= 0) {
        return index;
    }

    widget->setParent(this);
    listWidget.append(widget);
    return widgetCount() - 1;
}

int XStackWidget::indexOf(QWidget *widget) const
{
    return listWidget.indexOf(widget);
}

int XStackWidget::insertWidget(int index, QWidget *widget)
{
    int curindex = indexOf(widget);
    if (curindex >= 0) {
        return curindex;
    }

    widget->setParent(this);
    listWidget.insert(index, widget);
    return index;
}

QWidget *XStackWidget::currentWidget() const
{
    if (currentIndex >= 0 && currentIndex < widgetCount()) {
        return listWidget.at(currentIndex);
    }
    return 0;
}

QWidget *XStackWidget::widget(int index) const
{
    if (index >= 0 && index < widgetCount()) {
        return listWidget.at(index);
    }
    return 0;
}

void XStackWidget::removeWidget(QWidget *widget)
{
    int index = indexOf(widget);
    if (index >= 0) {
        listWidget.removeAll(widget);
        emit widgetRemoved(index);
    }
}

void XStackWidget::setCurrentWidget(QWidget *widget)
{
    int index = indexOf(widget);
    if (index >= 0 && currentIndex != index) {
        setCurrentIndex(index);
    }
}

void XStackWidget::setCurrentIndex(int index)
{
    if (index >= 0 && currentIndex != index) {
        lastIndex = currentIndex;
        currentIndex = index;
        moveAnimationStart();
        emit currentChanged(index);
    }
}

void XStackWidget::onValueChanged(const QVariant &value)
{
    offset = value.toInt();
    listWidget.at(currentIndex)->move(offset, 0);
    if (currentIndex > lastIndex) {
        listWidget.at(lastIndex)->move(offset - this->width(), 0);
    } else if (currentIndex < lastIndex) {
        listWidget.at(lastIndex)->move(this->width() + offset, 0);
    }
}

void XStackWidget::moveAnimationStart()
{
    animation->stop();
    setWidgetsVisible();

    int startOffset = offset;
    if (currentIndex > lastIndex) {
        if (startOffset == 0) {
            startOffset = this->width();
        } else {
            startOffset = this->width() - qAbs(startOffset);
        }
    } else {
        if (startOffset == 0) {
            startOffset = -this->width();
        } else {
            startOffset = qAbs(startOffset) - this->width();
        }
    }

    animation->setDuration(qAbs(startOffset) * duration / this->width());
    animation->setStartValue(startOffset);
    animation->setEndValue(0);
    animation->start();
}

void XStackWidget::setWidgetsVisible()
{
    int size = widgetCount();
    for (int i = 0; i < size; i++) {
        if (lastIndex == i || currentIndex == i) {
            listWidget.at(i)->setVisible(true);
        } else {
            listWidget.at(i)->setVisible(false);
        }
    }
}

void XStackWidget::onMoveFinished()
{

}
