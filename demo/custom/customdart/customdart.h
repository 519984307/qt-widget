#ifndef CUSTOMDART_H
#define CUSTOMDART_H

/**
 * 自定义飞镖盘控件 作者:东门吹雪(QQ:709102202) 整理:feiyangqingyun(QQ:517216493) 2022-03-02
 * 1. 可设置背景颜色。
 * 2. 可设置文字颜色。
 * 3. 可设置扇形交替颜色。
 * 4. 可设置扇形数量。
 * 5. 可设置扇形文本集合。
 * 6. 可设置扇形大小。
 * 7. 可设置扇形偏移值。
 */

#include <QWidget>

#ifdef quc
class Q_DECL_EXPORT CustomDart : public QWidget
#else
class CustomDart : public QWidget
#endif

{
    Q_OBJECT

    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(QColor fanColor1 READ getFanColor1 WRITE setFanColor1)
    Q_PROPERTY(QColor fanColor2 READ getFanColor2 WRITE setFanColor2)

    Q_PROPERTY(int fanSize READ getFanSize WRITE setFanSize)
    Q_PROPERTY(int fanOffset READ getFanOffset WRITE setFanOffset)
    Q_PROPERTY(int fanCount READ getFanCount WRITE setFanCount)
    Q_PROPERTY(QString fanText READ getFanText WRITE setFanText)

public:
    explicit CustomDart(QWidget *parent = 0);
    ~CustomDart();

protected:
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawArc(QPainter *painter, int radius, int angle, int len, const QColor &color);
    void drawFan(QPainter *painter);
    void drawText(QPainter *painter);

private:
    QColor bgColor;             //背景颜色
    QColor textColor;           //文字颜色
    QColor fanColor1;           //扇形颜色1
    QColor fanColor2;           //扇形颜色2

    int fanSize;                //扇形尺寸
    int fanOffset;              //扇形偏移值
    int fanCount;               //扇形数量
    QString fanText;            //扇形文本集合

public:
    QColor getBgColor()         const;
    QColor getTextColor()       const;
    QColor getFanColor1()       const;
    QColor getFanColor2()       const;

    int getFanSize()            const;
    int getFanOffset()          const;
    int getFanCount()           const;
    QString getFanText()        const;

    QSize sizeHint()            const;
    QSize minimumSizeHint()     const;

public Q_SLOTS:
    //设置背景颜色+文字颜色
    void setBgColor(const QColor &bgColor);
    void setTextColor(const QColor &textColor);

    //设置扇形交替颜色
    void setFanColor1(const QColor &fanColor1);
    void setFanColor2(const QColor &fanColor2);

    //设置扇形尺寸+扇形偏移值
    void setFanSize(int fanSize);
    void setFanOffset(int fanOffset);

    //设置扇形数量+扇形文本集合
    void setFanCount(int fanCount);
    void setFanText(const QString &fanText);    
};

#endif // CUSTOMDART_H
