#pragma execution_character_set("utf-8")

#include "timeaxis.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "qdebug.h"

TimeAxis::TimeAxis(QWidget *parent)	: QScrollArea(parent)
{
    itemMargin = 10;
    itemHeight = 70;
    infoPadding = 5;
    infoHeight = 40;

    baseColor = QColor("#8E44AD");
    lineColor = QColor("#BFBFBF");

    title = "公司发展历程";

    QStringList list;
    list << "2010.07,公司成立" << "2010.08,研发部成立" << "2011.5,产品发布上线";
    list << "2012.02,成立上海研发中心" << "2012.12,年营业额突破1亿" << "2013.6,重量级核心产品问世";
    list << "2014.11,成立各级分销中心" << "2015.03,总营业额突破10亿" << "2017.5,公司上市";

    timeAxisWidget = new TimeAxisWidget(this);
    this->setInfos(list.join("|"));
    this->setWidget(timeAxisWidget);
    this->setFrameShape(QFrame::NoFrame);
    this->setWidgetResizable(true);
    this->viewport()->setStyleSheet("background-color:transparent;");
}

int TimeAxis::getItemMargin() const
{
    return timeAxisWidget->getItemMargin();
}

int TimeAxis::getItemHeight() const
{
    return timeAxisWidget->getItemHeight();
}

int TimeAxis::getInfoPadding() const
{
    return timeAxisWidget->getInfoPadding();
}

int TimeAxis::getInfoHeight() const
{
    return timeAxisWidget->getInfoHeight();
}

QColor TimeAxis::getBaseColor() const
{
    return timeAxisWidget->getBaseColor();
}

QColor TimeAxis::getLineColor() const
{
    return timeAxisWidget->getLineColor();
}

QString TimeAxis::getTitle() const
{
    return timeAxisWidget->getTitle();
}

QString TimeAxis::getInfos() const
{
    return timeAxisWidget->getInfos();
}

QSize TimeAxis::sizeHint() const
{
    return QSize(500, 500);
}

QSize TimeAxis::minimumSizeHint() const
{
    return QSize(300, 100);
}

TimeAxisWidget *TimeAxis::getWidget()
{
    return this->timeAxisWidget;
}

void TimeAxis::setItemMargin(int itemMargin)
{
    timeAxisWidget->setItemMargin(itemMargin);
}

void TimeAxis::setItemHeight(int itemHeight)
{
    timeAxisWidget->setItemHeight(itemHeight);
}

void TimeAxis::setInfoPadding(int infoPadding)
{
    timeAxisWidget->setInfoPadding(infoPadding);
}

void TimeAxis::setInfoHeight(int infoHeight)
{
    timeAxisWidget->setInfoHeight(infoHeight);
}

void TimeAxis::setBaseColor(const QColor &baseColor)
{
    timeAxisWidget->setBaseColor(baseColor);
}

void TimeAxis::setLineColor(const QColor &lineColor)
{
    timeAxisWidget->setLineColor(lineColor);
}

void TimeAxis::setTitle(const QString &title)
{
    timeAxisWidget->setTitle(title);
}

void TimeAxis::setInfos(const QString &infos)
{
    timeAxisWidget->setInfos(infos);
}


TimeAxisWidget::TimeAxisWidget(QWidget *parent) : QWidget(parent)
{
    itemMargin = 10;
    itemHeight = 70;
    infoPadding = 5;
    infoHeight = 40;

    baseColor = QColor("#8E44AD");
    lineColor = QColor("#BFBFBF");

    title = "公司发展历程";

    QStringList list;
    list << "2010.07,公司成立" << "2010.08,研发部成立" << "2011.5,产品发布上线";
    list << "2012.02,成立上海研发中心" << "2012.12,年营业额突破1亿" << "2013.6,重量级核心产品问世";
    list << "2014.11,成立各级分销中心" << "2015.03,总营业额突破10亿" << "2017.5,公司上市";
    this->setInfos(list.join("|"));
}

void TimeAxisWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制标题
    drawTitle(&painter);
    //绘制垂直线
    drawLine(&painter);
    //绘制信息
    drawInfo(&painter);
}

void TimeAxisWidget::drawTitle(QPainter *painter)
{
    painter->save();

    QFont font;
    font.setBold(true);
    font.setPointSize(16);
    painter->setFont(font);

    painter->setPen(baseColor);
    painter->drawText(itemMargin, itemMargin, width() - 2 * itemMargin, 40, Qt::AlignCenter, title);

    painter->restore();
}

void TimeAxisWidget::drawLine(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(lineColor, 6));
    int startY = itemMargin + 50;
    int endY = startY + itemInfos.size() * itemHeight;
    painter->drawLine(width() / 2.0, startY, width() / 2.0, endY);
    painter->restore();

    //设置下固定高度
    this->setFixedHeight(endY + itemMargin);
}

void TimeAxisWidget::drawInfo(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QFont font;
    font.setPointSize(12);
    painter->setFont(font);

    int startY = itemMargin + 50;
    int centerX = this->width() / 2.0;
    int spacer = itemMargin + 10;

    //追个绘制时间轴信息集合,偶数行左侧绘制时间右侧绘制信息
    for (int i = 0; i < itemInfos.size(); i++) {
        painter->setBrush(Qt::white);
        painter->setPen(QPen(baseColor, 2));

        if (i % 2 == 0) {
            //绘制时间
            QRectF textRect(0, startY, centerX - spacer, itemHeight);
            painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, itemInfos.at(i).time);
            //绘制信息边框
            QRectF infoRect(centerX + spacer, textRect.center().y() - infoHeight / 2.0, centerX - spacer - itemMargin - infoHeight / 2.0, infoHeight);
            drawInfoRight(painter, infoRect, infoHeight);
            //绘制信息背景
            painter->setBrush(baseColor);
            drawInfoRight(painter, infoRect.adjusted(infoPadding, infoPadding, 0, -infoPadding), infoHeight - infoPadding * 2);
            //绘制信息文字
            painter->setPen(Qt::white);
            painter->drawText(infoRect.adjusted(infoPadding, infoPadding, 0, -infoPadding), Qt::AlignCenter, itemInfos.at(i).info);
        } else {
            //绘制时间
            QRectF textRect(centerX + spacer, startY, centerX - spacer, itemHeight);
            painter->drawText(centerX + spacer, startY, centerX - spacer, itemHeight, Qt::AlignLeft | Qt::AlignVCenter, itemInfos.at(i).time);
            //绘制信息边框
            QRectF infoRect(itemMargin + infoHeight / 2.0, textRect.center().y() - infoHeight / 2.0, centerX - spacer - itemMargin - infoHeight / 2.0, infoHeight);
            drawInfoLeft(painter, infoRect, infoHeight);
            //绘制信息背景
            painter->setBrush(baseColor);
            drawInfoLeft(painter, infoRect.adjusted(0, infoPadding, -infoPadding, -infoPadding), infoHeight - infoPadding * 2);
            //绘制信息文字
            painter->setPen(Qt::white);
            painter->drawText(infoRect.adjusted(0, infoPadding, -infoPadding, -infoPadding), Qt::AlignCenter, itemInfos.at(i).info);
        }

        //绘制垂直线对应的圆
        painter->setPen(Qt::NoPen);
        painter->setBrush(baseColor);
        painter->drawEllipse(centerX - 8, startY + itemHeight / 2.0 - 8, 16, 16);
        painter->setBrush(Qt::white);
        painter->drawEllipse(centerX - 4, startY + itemHeight / 2.0 - 4, 8, 8);

        //Y轴往下移一个高度
        startY += itemHeight;
    }

    painter->restore();
}

void TimeAxisWidget::drawInfoRight(QPainter *painter, const QRectF &infoRect, int infoHeight)
{
    QPainterPath path;
    path.moveTo(infoRect.topRight());
    path.lineTo(infoRect.topLeft());
    path.lineTo(infoRect.bottomLeft());
    path.lineTo(infoRect.bottomRight());
    path.arcTo(infoRect.right() - infoHeight / 2.0, infoRect.top(), infoHeight, infoHeight, -90, 180);
    painter->drawPath(path);
}

void TimeAxisWidget::drawInfoLeft(QPainter *painter, const QRectF &infoRect, int infoHeight)
{
    QPainterPath path;
    path.moveTo(infoRect.bottomLeft());
    path.lineTo(infoRect.bottomRight());
    path.lineTo(infoRect.topRight());
    path.lineTo(infoRect.topLeft());
    path.arcTo(infoRect.left() - infoHeight / 2.0, infoRect.top(), infoHeight, infoHeight, 90, 180);
    painter->drawPath(path);
}

int TimeAxisWidget::getItemMargin() const
{
    return this->itemMargin;
}

int TimeAxisWidget::getItemHeight() const
{
    return this->itemHeight;
}

int TimeAxisWidget::getInfoPadding() const
{
    return this->infoPadding;
}

int TimeAxisWidget::getInfoHeight() const
{
    return this->infoHeight;
}

QColor TimeAxisWidget::getBaseColor() const
{
    return this->baseColor;
}

QColor TimeAxisWidget::getLineColor() const
{
    return this->lineColor;
}

QString TimeAxisWidget::getTitle() const
{
    return this->title;
}

QString TimeAxisWidget::getInfos() const
{
    return this->infos;
}

QSize TimeAxisWidget::sizeHint() const
{
    return QSize(500, 500);
}

QSize TimeAxisWidget::minimumSizeHint() const
{
    return QSize(300, 100);
}

void TimeAxisWidget::setItemMargin(int itemMargin)
{
    if (this->itemMargin != itemMargin) {
        this->itemMargin = itemMargin;
        this->update();;
    }
}

void TimeAxisWidget::setItemHeight(int itemHeight)
{
    if (this->itemHeight != itemHeight) {
        this->itemHeight = itemHeight;
        this->update();;
    }
}

void TimeAxisWidget::setInfoPadding(int infoPadding)
{
    if (this->infoPadding != infoPadding) {
        this->infoPadding = infoPadding;
        this->update();;
    }
}

void TimeAxisWidget::setInfoHeight(int infoHeight)
{
    if (this->infoHeight != infoHeight) {
        this->infoHeight = infoHeight;
        this->update();;
    }
}

void TimeAxisWidget::setBaseColor(const QColor &baseColor)
{
    if (this->baseColor != baseColor) {
        this->baseColor = baseColor;
        this->update();
    }
}

void TimeAxisWidget::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->update();
    }
}

void TimeAxisWidget::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        this->update();
    }
}

void TimeAxisWidget::setInfos(const QString &infos)
{
    if (this->infos != infos) {
        this->infos = infos;

        //组成结构体模式
        QStringList list = infos.split("|");
        QList<TimeAxisInfo> itemInfos;
        for (int i = 0; i < list.count(); i++) {
            QStringList l = list.at(i).split(",");
            if (l.count() == 2) {
                TimeAxisInfo itemInfo;
                itemInfo.time = l.at(0);
                itemInfo.info = l.at(1);
                itemInfos << itemInfo;
            }
        }

        setItemInfos(itemInfos);
    }
}

void TimeAxisWidget::setItemInfos(const QList<TimeAxisInfo> &itemInfos)
{
    this->itemInfos = itemInfos;
    this->update();
}
