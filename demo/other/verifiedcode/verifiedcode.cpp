#pragma execution_character_set("utf-8")

#include "verifiedcode.h"
#include "qpainter.h"
#include "qdatetime.h"
#include "qdebug.h"

VerifiedCode::VerifiedCode(QWidget *parent) : QWidget(parent)
{
    codeLen = 4;
    noiseCount = 20;
    lineCount = 5;

    listCode << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9"
             << "a" << "b" << "c" << "d" << "e" << "f" << "g" << "h" << "i" << "j"
             << "k" << "l" << "m" << "n" << "o" << "p" << "q" << "r" << "s" << "t"
             << "u" << "v" << "w" << "x" << "y" << "z"
             << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "H" << "I" << "J"
             << "K" << "L" << "M" << "N" << "O" << "P" << "Q" << "R" << "S" << "T"
             << "U" << "V" << "W" << "X" << "Y" << "Z";

    colorList = QColor::colorNames();

    updateCode();
    QFont font;
    font.setFamily("Arial");
    font.setPixelSize(28);
    setFont(font);
}

VerifiedCode::~VerifiedCode()
{

}

void VerifiedCode::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制随机噪点
    drawRoise(&painter);
    //绘制随机干扰线
    drawLine(&painter);
    //绘制验证码字符串
    drawCode(&painter);
}

void VerifiedCode::drawRoise(QPainter *painter)
{
    painter->save();

    QPen pen;
    pen.setWidth(2);

    for (int i = 0; i < noiseCount; i++) {
        pen.setColor(colorList.at(rand() % colorList.count()));
        painter->setPen(pen);
        painter->drawPoint(QPointF(rand() % width(), rand() % height()));
    }

    painter->restore();
}

void VerifiedCode::drawLine(QPainter *painter)
{
    painter->save();

    QPen pen;
    pen.setWidth(3);

    for (int i = 0; i < lineCount; i++) {
        pen.setColor(colorList.at(rand() % colorList.count()));
        painter->setPen(pen);
        QPoint p1(rand() % width(), rand() % height());
        QPoint p2(rand() % width(), rand() % height());
        painter->drawLine(p1, p2);
    }

    painter->restore();
}

void VerifiedCode::drawCode(QPainter *painter)
{
    painter->save();

    static const int sineTable[16] = {
        0, 38, 71, 92, 100, 92, 71, 38, 0, -38, -71, -92, -100, -92, -71, -38
    };

    QFontMetrics metrics(font());
#if (QT_VERSION >= QT_VERSION_CHECK(5,11,0))
    int x = (width() - metrics.horizontalAdvance(code)) / 2;
#else
    int x = (width() - metrics.width(code)) / 2;
#endif
    int y = (height() + metrics.ascent() - metrics.descent()) / 2;
    QColor color;

    for (int i = 0; i < code.size(); ++i) {
        int index = i % 16;
        color.setHsv((15 - index) * 16, 255, 191);
        painter->setPen(color);
        painter->drawText(x, y - ((sineTable[index] * metrics.height()) / 400), code.at(i));
#if (QT_VERSION >= QT_VERSION_CHECK(5,11,0))
        x += metrics.horizontalAdvance(code.at(i));
#else
        x += metrics.width(code.at(i));
#endif
    }

    painter->drawText(rect(), Qt::AlignCenter, code);

    painter->restore();
}

void VerifiedCode::updateCode()
{
    //生成随机验证码字符串
    code.clear();
    for (int i = 0; i < codeLen; i++) {
        code.append(listCode.at(rand() % listCode.count()));
    }
}

int VerifiedCode::getCodeLen() const
{
    return this->codeLen;
}

int VerifiedCode::getNoiseCount() const
{
    return this->noiseCount;
}

int VerifiedCode::getLineCount() const
{
    return this->lineCount;
}

QString VerifiedCode::getCode() const
{
    return this->code;
}

QSize VerifiedCode::sizeHint() const
{
    return QSize(100, 50);
}

QSize VerifiedCode::minimumSizeHint() const
{
    return QSize(20, 20);
}

void VerifiedCode::loadCode()
{
    updateCode();
    this->update();
}

void VerifiedCode::setCodeLen(int codeLen)
{
    if (this->codeLen != codeLen) {
        this->codeLen = codeLen;
        updateCode();
        this->update();
    }
}

void VerifiedCode::setNoiseCount(int noiseCount)
{
    if (this->noiseCount != noiseCount) {
        this->noiseCount = noiseCount;
        this->update();
    }
}

void VerifiedCode::setLineCount(int lineCount)
{
    if (this->lineCount != lineCount) {
        this->lineCount = lineCount;
        this->update();
    }
}
