#pragma execution_character_set("utf-8")

#include "navbuttongroup.h"
#include "qpainter.h"
#include "qevent.h"
#include "qabstractbutton.h"
#include "qpushbutton.h"
#include "qbuttongroup.h"
#include "qpropertyanimation.h"
#include "qlayout.h"
#include "qtimer.h"
#include "qdebug.h"

NavButtonGroup::NavButtonGroup(QWidget *parent) : QWidget(parent)
{
    interval = 300;
    lineLen = 3;
    texts = "";
    linePosition = LinePosition_Top;

    lineColor = QColor(34, 163, 169);
    btnNormalColor = QColor(255, 255, 255);
    btnHoverColor = QColor(34, 163, 169, 100);
    btnDarkColor = QColor(34, 163, 169, 180);
    textNormalColor = QColor(0, 0, 0);
    textHoverColor = QColor(255, 255, 255);
    textDarkColor = QColor(255, 255, 255);
    baseColor = QColor(34, 163, 169);

    index = 0;
    previousIndex = 0;
    offset = 0;
    btnSize = QSize(30, 30);
    layout = 0;

    btnGroup = new QButtonGroup(this);
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    connect(btnGroup, SIGNAL(idClicked(int)), SLOT(onButtonClicked(int)));
#else
    connect(btnGroup, SIGNAL(buttonClicked(int)), SLOT(onButtonClicked(int)));
#endif

    animation = new QPropertyAnimation(this, "");
    animation->setDuration(interval);
    connect(animation, SIGNAL(valueChanged(QVariant)), SLOT(onValueChanged(QVariant)));

    //默认在底部
    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, lineLen, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);

    //设置初始集合
    QStringList list;
    list << "学生管理" << "教师管理" << "成绩管理" << "成绩查询" << "系统设置";
    for (int i = 0; i < 5; i++) {
        QPushButton *btn = new QPushButton;
        btn->setCheckable(true);
        btn->setText(list.at(i));
        btn->setMinimumHeight(30);
        //btn->setFixedSize(80, 30);
        this->addButton((QAbstractButton *)btn, i);
    }
}

NavButtonGroup::~NavButtonGroup()
{
}

void NavButtonGroup::resizeEvent(QResizeEvent *)
{
    //尺寸改变的时候要重新计算并绘制
    this->init();
}

void NavButtonGroup::showEvent(QShowEvent *)
{
    //显示时需要重新计算并绘制
    this->init();
}

void NavButtonGroup::paintEvent(QPaintEvent *)
{
    if (btns.count() == 0) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    //设置颜色
    painter.setPen(Qt::NoPen);
    painter.setBrush(lineColor);

    //根据不同的位置绘制线条区域,也可以改成绘制两点之间的距离
    if (linePosition == LinePosition_Top) {
        painter.drawRect(offset, 0, btnSize.width(), lineLen);
    } else if (linePosition == LinePosition_Bottom) {
        painter.drawRect(offset, this->height() - lineLen, btnSize.width(), lineLen);
    } else if (linePosition == LinePosition_Left) {
        painter.drawRect(0, offset, lineLen, btnSize.height());
    } else if (linePosition == LinePosition_Right) {
        painter.drawRect(this->width() - lineLen, offset, lineLen, btnSize.height());
    }
}

void NavButtonGroup::onButtonClicked(int index)
{
    //当前按钮选中
    btnGroup->button(index)->setChecked(true);

    //更新当前按钮和上一个按钮的索引
    previousIndex = this->index;
    this->index = index;

    //根据线条位置设置动画启动和结束值
    if (linePosition == LinePosition_Top || linePosition == LinePosition_Bottom) {
        animation->setStartValue(btns.at(previousIndex)->x());
        animation->setEndValue(btns.at(index)->x());
    } else if (linePosition == LinePosition_Left || linePosition == LinePosition_Right) {
        animation->setStartValue(btns.at(previousIndex)->y());
        animation->setEndValue(btns.at(index)->y());
    }

    //启动动画移动线条
    animation->start();

    //发送信号出去
    emit buttonClicked(index);
    emit buttonClicked(btns.at(index));
}

void NavButtonGroup::onValueChanged(const QVariant &value)
{
    offset = value.toInt();
    this->update();
}

int NavButtonGroup::getInterval() const
{
    return this->interval;
}

int NavButtonGroup::getLineLen() const
{
    return this->lineLen;
}

int NavButtonGroup::getIndex() const
{
    return this->index;
}

QString NavButtonGroup::getTexts() const
{
    return this->texts;
}

NavButtonGroup::LinePosition NavButtonGroup::getLinePosition() const
{
    return this->linePosition;
}

QColor NavButtonGroup::getLineColor() const
{
    return this->lineColor;
}

QColor NavButtonGroup::getBtnNormalColor() const
{
    return this->btnNormalColor;
}

QColor NavButtonGroup::getBtnHoverColor() const
{
    return this->btnHoverColor;
}

QColor NavButtonGroup::getBtnDarkColor() const
{
    return this->btnDarkColor;
}

QColor NavButtonGroup::getTextNormalColor() const
{
    return this->textNormalColor;
}

QColor NavButtonGroup::getTextHoverColor() const
{
    return this->textHoverColor;
}

QColor NavButtonGroup::getTextDarkColor() const
{
    return this->textDarkColor;
}

QColor NavButtonGroup::getBaseColor() const
{
    return this->baseColor;
}

QSize NavButtonGroup::sizeHint() const
{
    return QSize(500, 30);
}

QSize NavButtonGroup::minimumSizeHint() const
{
    return QSize(20, 20);
}

void NavButtonGroup::setInterval(int interval)
{
    if (this->interval != interval) {
        this->interval = interval;
        animation->setDuration(interval);
        this->update();
    }
}

void NavButtonGroup::setLineLen(int lineLen)
{
    if (this->lineLen != lineLen) {
        this->lineLen = lineLen;
        this->update();
    }
}

void NavButtonGroup::setIndex(int index)
{
    if (index < btns.count() && this->index != index) {
        this->index = index;
        btns.at(index)->click();
    }
}

void NavButtonGroup::setTexts(const QString &texts)
{
    if (this->texts != texts && !texts.isEmpty()) {
        QStringList list = texts.split(";");
        if (list.count() == 0) {
            return;
        }

        this->texts = texts;
        index = 0;
        previousIndex = 0;
        offset = 0;

        //清空原有按钮
        qDeleteAll(btns);
        btns.clear();

        //重新逐个根据文本分割实例化按钮加入
        for (int i = 0; i < list.count(); i++) {
            QPushButton *btn = new QPushButton;
            btn->setCheckable(true);
            btn->setText(list.at(i));
            btn->setMinimumHeight(30);
            this->addButton((QAbstractButton *)btn, i);
        }

        //重新初始化,以便线条立即跟踪过去
        QMetaObject::invokeMethod(this, "init");
    }
}

void NavButtonGroup::setLinePosition(const NavButtonGroup::LinePosition &linePosition)
{
    if (this->linePosition != linePosition) {
        this->linePosition = linePosition;

        //清除布局
        if (layout != 0) {
            delete layout;
            layout = 0;
        }

        //重新设置布局
        if (linePosition == LinePosition_Top) {
            layout = new QHBoxLayout(this);
            layout->setContentsMargins(0, lineLen, 0, 0);
        } else if (linePosition == LinePosition_Bottom) {
            layout = new QHBoxLayout(this);
            layout->setContentsMargins(0, 0, 0, lineLen);
        } else if (linePosition == LinePosition_Left) {
            layout = new QVBoxLayout(this);
            layout->setContentsMargins(lineLen, 0, 0, 0);
        } else if (linePosition == LinePosition_Right) {
            layout = new QVBoxLayout(this);
            layout->setContentsMargins(0, 0, lineLen, 0);
        }

        layout->setSpacing(0);
        setLayout(layout);

        //重新加载按钮到布局
        foreach (QAbstractButton *btn, btns) {
            layout->addWidget(btn);
        }

        //重新初始化,以便线条立即跟踪过去
        QMetaObject::invokeMethod(this, "init");
    }
}

void NavButtonGroup::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->setBtnStyle();
        this->update();
    }
}

void NavButtonGroup::setBtnNormalColor(const QColor &btnNormalColor)
{
    if (this->btnNormalColor != btnNormalColor) {
        this->btnNormalColor = btnNormalColor;
        this->setBtnStyle();
        this->update();
    }
}

void NavButtonGroup::setBtnHoverColor(const QColor &btnHoverColor)
{
    if (this->btnHoverColor != btnHoverColor) {
        this->btnHoverColor = btnHoverColor;
        this->setBtnStyle();
        this->update();
    }
}

void NavButtonGroup::setBtnDarkColor(const QColor &btnDarkColor)
{
    if (this->btnDarkColor != btnDarkColor) {
        this->btnDarkColor = btnDarkColor;
        this->setBtnStyle();
        this->update();
    }
}

void NavButtonGroup::setTextNormalColor(const QColor &textNormalColor)
{
    if (this->textNormalColor != textNormalColor) {
        this->textNormalColor = textNormalColor;
        this->setBtnStyle();
        this->update();
    }
}

void NavButtonGroup::setTextHoverColor(const QColor &textHoverColor)
{
    if (this->textHoverColor != textHoverColor) {
        this->textHoverColor = textHoverColor;
        this->setBtnStyle();
        this->update();
    }
}

void NavButtonGroup::setTextDarkColor(const QColor &textDarkColor)
{
    if (this->textDarkColor != textDarkColor) {
        this->textDarkColor = textDarkColor;
        this->setBtnStyle();
        this->update();
    }
}

void NavButtonGroup::setBaseColor(const QColor &baseColor, bool normal)
{
    if (this->baseColor != baseColor) {
        this->baseColor = baseColor;

        //根据基准颜色设置其他颜色
        if (normal) {
            this->btnNormalColor = this->baseColor;
        }

        this->lineColor = this->baseColor;
        this->baseColor.setAlpha(100);
        this->btnHoverColor = this->baseColor;
        this->baseColor.setAlpha(180);
        this->btnDarkColor = this->baseColor;
        this->setBtnStyle();

        this->update();
    }
}

void NavButtonGroup::init()
{
    //首次显示重新纠正按钮尺寸大小
    if (btns.count() > 0) {
        btnSize = btns.at(0)->size();
        btns.at(index)->click();
    }
}

void NavButtonGroup::addButton(QAbstractButton *btn, int id)
{
    layout->addWidget(btn);
    btns.append(btn);
    btnGroup->addButton(btn, id);

    //按钮的样式,可以自行拓展比如圆角
    QStringList qss;
    qss.append(QString("QAbstractButton{border:none;background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);}")
               .arg(btnNormalColor.red()).arg(btnNormalColor.green()).arg(btnNormalColor.blue()).arg(btnNormalColor.alpha())
               .arg(textNormalColor.red()).arg(textNormalColor.green()).arg(textNormalColor.blue()).arg(textNormalColor.alpha()));
    qss.append(QString("QAbstractButton:hover{background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);}")
               .arg(btnHoverColor.red()).arg(btnHoverColor.green()).arg(btnHoverColor.blue()).arg(btnHoverColor.alpha())
               .arg(textHoverColor.red()).arg(textHoverColor.green()).arg(textHoverColor.blue()).arg(textHoverColor.alpha()));
    qss.append(QString("QAbstractButton:pressed,QAbstractButton:checked{background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);}")
               .arg(btnDarkColor.red()).arg(btnDarkColor.green()).arg(btnDarkColor.blue()).arg(btnDarkColor.alpha())
               .arg(textDarkColor.red()).arg(textDarkColor.green()).arg(textDarkColor.blue()).arg(textDarkColor.alpha()));
    btn->setStyleSheet(qss.join(""));

    //获取所有按钮的文本集合
    QStringList list;
    foreach (QAbstractButton *btn, btns) {
        list.append(btn->text());
    }

    texts = list.join(";");
}

void NavButtonGroup::clearButton()
{
    foreach (QAbstractButton *btn, btns) {
        layout->removeWidget(btn);
        btnGroup->removeButton(btn);
    }

    qDeleteAll(btns);
    btns.clear();
}

void NavButtonGroup::addFinsh()
{
    //添加末尾拉伸弹簧
    layout->addStretch();
}

void NavButtonGroup::setBtnStyle()
{
    //按钮的样式,可以自行拓展比如圆角
    QStringList qss;
    qss.append(QString("QAbstractButton{border:none;background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);}")
               .arg(btnNormalColor.red()).arg(btnNormalColor.green()).arg(btnNormalColor.blue()).arg(btnNormalColor.alpha())
               .arg(textNormalColor.red()).arg(textNormalColor.green()).arg(textNormalColor.blue()).arg(textNormalColor.alpha()));
    qss.append(QString("QAbstractButton:hover{background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);}")
               .arg(btnHoverColor.red()).arg(btnHoverColor.green()).arg(btnHoverColor.blue()).arg(btnHoverColor.alpha())
               .arg(textHoverColor.red()).arg(textHoverColor.green()).arg(textHoverColor.blue()).arg(textHoverColor.alpha()));
    qss.append(QString("QAbstractButton:pressed,QAbstractButton:checked{background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);}")
               .arg(btnDarkColor.red()).arg(btnDarkColor.green()).arg(btnDarkColor.blue()).arg(btnDarkColor.alpha())
               .arg(textDarkColor.red()).arg(textDarkColor.green()).arg(textDarkColor.blue()).arg(textDarkColor.alpha()));

    foreach (QAbstractButton *btn, btns) {
        btn->setStyleSheet(qss.join(""));
    }
}
