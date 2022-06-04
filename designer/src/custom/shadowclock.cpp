#pragma execution_character_set("utf-8")

#include "shadowclock.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "qdatetime.h"
#include "qpropertyanimation.h"
#include "qdebug.h"

ShadowClock::ShadowClock(QWidget *parent) : QWidget(parent)
{
    radiusWidth = 6;
    shadowWidth = 4;

    textColor = QColor("#22A3A9");
    shadowColor = QColor("#22A3A9");
    hourColor = QColor("#22A3A9");
    minuteColor = QColor("#22A3A9");
    secondColor = QColor("#22A3A9");

    //采用动画机制,产生过渡效果
    QPropertyAnimation *animation = new QPropertyAnimation(this, "");
    connect(animation, SIGNAL(valueChanged(QVariant)), this, SLOT(update()));
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(20);
    animation->setLoopCount(-1);
    animation->start();
}

ShadowClock::~ShadowClock()
{

}

void ShadowClock::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2.0, height / 2.0);
    painter.scale(side / 200.0, side / 200.0);

    //绘制时圆弧
    QDateTime now = QDateTime::currentDateTime();
    QTime time = now.time();
    int hour = time.hour() >= 12 ? time.hour() - 12 : time.hour();
    int min = time.minute();
    int sec = time.second();
    int msec = time.msec();

    qreal dsec = sec + msec / 1000.0;
    qreal dmin = min + dsec / 60.0;
    qreal dhour = hour + dmin / 60.0;

    //绘制时圆弧
    drawArc(&painter, 94, dhour * 30, hourColor);
    //绘制分圆弧
    drawArc(&painter, 81, dmin * 6, minuteColor);
    //绘制秒圆弧
    drawArc(&painter, 68, dsec * 6, secondColor);
    //绘制时间文本
    drawText(&painter);
}

void ShadowClock::drawArc(QPainter *painter, int radius, qreal angle, const QColor &arcColor)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    int smallradius = radius - radiusWidth;
    int maxRaidus = radius + shadowWidth;
    int minRadius = smallradius - shadowWidth;

    //采用圆形渐变,形成光晕效果
    QRadialGradient radialGradient(QPointF(0, 0), maxRaidus);
    QColor color = arcColor;
    QColor lightColor = arcColor.lighter(100);

    color.setAlphaF(0);
    radialGradient.setColorAt(0, color);
    radialGradient.setColorAt(minRadius * 1.0 / maxRaidus, color);
    color.setAlphaF(0.5);
    radialGradient.setColorAt(smallradius * 1.0 / maxRaidus, color);

    radialGradient.setColorAt((smallradius + 1) * 1.0 / maxRaidus, lightColor);
    radialGradient.setColorAt((radius - 1) * 1.0 / maxRaidus, lightColor);
    radialGradient.setColorAt(radius * 1.0 / maxRaidus, color);
    color.setAlphaF(0);
    radialGradient.setColorAt(1, color);

    painter->setBrush(radialGradient);
    painter->drawPie(-maxRaidus, -maxRaidus, maxRaidus * 2, maxRaidus * 2, 90 * 16, -angle * 16);
    painter->restore();
}

void ShadowClock::drawText(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QFont font;
    font.setBold(true);
    font.setPointSize(10);
    painter->setFont(font);

    QDateTime now = QDateTime::currentDateTime();
    QFontMetricsF fm(font);
    QStringList textList;
    textList << now.toString("MM月dd日yyyy") << now.toString("hh:mm:ss.zzz");

    //绘制文本路径
    QPainterPath textPath;
#if (QT_VERSION >= QT_VERSION_CHECK(5,11,0))
    int textWidth1 = fm.horizontalAdvance(textList.at(0));
    int textWidth2 = fm.horizontalAdvance(textList.at(1));
#else
    int textWidth1 = fm.width(textList.at(0));
    int textWidth2 = fm.width(textList.at(1));
#endif
    textPath.addText(-textWidth1 / 2.0, -fm.lineSpacing() / 2.0, font, textList.at(0));
    textPath.addText(-textWidth2 / 2.0, fm.lineSpacing() / 2.0, font, textList.at(1));

    QColor strokeColor = textColor.lighter(80);
    strokeColor.setAlphaF(0.2);
    painter->strokePath(textPath, QPen(strokeColor, shadowWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(textColor);
    painter->drawPath(textPath);

    painter->restore();
}

int ShadowClock::getRadiusWidth() const
{
    return this->radiusWidth;
}

int ShadowClock::getShadowWidth() const
{
    return this->shadowWidth;
}

QColor ShadowClock::getTextColor() const
{
    return this->textColor;
}

QColor ShadowClock::getShadowColor() const
{
    return this->shadowColor;
}

QColor ShadowClock::getHourColor() const
{
    return this->hourColor;
}

QColor ShadowClock::getMinuteColor() const
{
    return this->minuteColor;
}

QColor ShadowClock::getSecondColor() const
{
    return this->secondColor;
}

QSize ShadowClock::sizeHint() const
{
    return QSize(200, 200);
}

QSize ShadowClock::minimumSizeHint() const
{
    return QSize(20, 20);
}

void ShadowClock::setRadiusWidth(int radiusWidth)
{
    if (this->radiusWidth != radiusWidth) {
        this->radiusWidth = radiusWidth;
        this->update();
    }
}

void ShadowClock::setShadowWidth(int shadowWidth)
{
    if (this->shadowWidth != shadowWidth) {
        this->shadowWidth = shadowWidth;
        this->update();
    }
}

void ShadowClock::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}

void ShadowClock::setShadowColor(const QColor &shadowColor)
{
    if (this->shadowColor != shadowColor) {
        this->shadowColor = shadowColor;
        this->hourColor = shadowColor;
        this->minuteColor = shadowColor;
        this->secondColor = shadowColor;
        this->update();
    }
}

void ShadowClock::setHourColor(const QColor &hourColor)
{
    if (this->hourColor != hourColor) {
        this->hourColor = hourColor;
        this->update();
    }
}

void ShadowClock::setMinuteColor(const QColor &minuteColor)
{
    if (this->minuteColor != minuteColor) {
        this->minuteColor = minuteColor;
        this->update();
    }
}

void ShadowClock::setSecondColor(const QColor &secondColor)
{
    if (this->secondColor != secondColor) {
        this->secondColor = secondColor;
        this->update();
    }
}
