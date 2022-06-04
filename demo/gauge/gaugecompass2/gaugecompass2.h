#ifndef GAUGECOMPASS2_H
#define GAUGECOMPASS2_H

/**
 * 指南针仪表盘2控件 作者:feiyangqingyun(QQ:517216493) 2022-02-11
 * 1. 可设置大刻度小刻度数量。
 * 2. 可设置刻度尺颜色。
 * 3. 可设置指针颜色。
 * 4. 可设置中间园渐变颜色。
 * 5. 可设置文字颜色。
 */

#include <QWidget>

#ifdef quc
class Q_DECL_EXPORT GaugeCompass2 : public QWidget
#else
class GaugeCompass2 : public QWidget
#endif

{
    Q_OBJECT

    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(int scaleMajor READ getScaleMajor WRITE setScaleMajor)
    Q_PROPERTY(int scaleMinor READ getScaleMinor WRITE setScaleMinor)

    Q_PROPERTY(QColor scaleColor READ getScaleColor WRITE setScaleColor)
    Q_PROPERTY(QColor pointerColor READ getPointerColor WRITE setPointerColor)
    Q_PROPERTY(QColor circleColor1 READ getCircleColor1 WRITE setCircleColor1)
    Q_PROPERTY(QColor circleColor2 READ getCircleColor2 WRITE setCircleColor2)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)

public:
    explicit GaugeCompass2(QWidget *parent = 0);
    ~GaugeCompass2();

protected:
    void paintEvent(QPaintEvent *);
    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawCircle(QPainter *painter);
    void drawText(QPainter *painter);
    void drawPointer(QPainter *painter);

private:
    double value;               //目标值
    int scaleMajor;             //大刻度数量
    int scaleMinor;             //小刻度数量

    QColor scaleColor;          //刻度尺颜色
    QColor pointerColor;        //指针颜色
    QColor circleColor1;        //中心圆颜色1
    QColor circleColor2;        //中心圆颜色2
    QColor textColor;           //文字颜色

public:
    double getValue()           const;
    int getScaleMajor()         const;
    int getScaleMinor()         const;

    QColor getScaleColor()      const;
    QColor getPointerColor()    const;
    QColor getCircleColor1()    const;
    QColor getCircleColor2()    const;
    QColor getTextColor()       const;

    QSize sizeHint()            const;
    QSize minimumSizeHint()     const;

public Q_SLOTS:
    //设置目标值
    void setValue(double value);
    void setValue(int value);

    //设置主刻度数量
    void setScaleMajor(int scaleMajor);
    //设置小刻度数量
    void setScaleMinor(int scaleMinor);

    //设置刻度尺颜色
    void setScaleColor(const QColor &scaleColor);
    //设置指针颜色
    void setPointerColor(const QColor &pointerColor);
    //设置中心圆颜色1
    void setCircleColor1(const QColor &circleColor1);
    //设置中心圆颜色2
    void setCircleColor2(const QColor &circleColor2);
    //设置文本颜色
    void setTextColor(const QColor &textColor);

Q_SIGNALS:
    void valueChanged(int value);
};

#endif // GAUGECOMPASS2_H
