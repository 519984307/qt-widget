﻿#ifndef BARVUMETER_H
#define BARVUMETER_H

/**
 * 音量条控件 作者:来源于网络 整理:feiyangqingyun(QQ:517216493) 2016-10-08
 * 1. 可设置最大值最小值范围值。
 * 2. 可设置左通道、右通道音量值。
 * 3. 可设置背景颜色。
 * 4. 可设置值进度颜色。
 * 5. 可设置大值颜色、小值颜色。
 */

#include <QWidget>

#ifdef quc
class Q_DECL_EXPORT BarVUMeter : public QWidget
#else
class BarVUMeter : public QWidget
#endif

{
    Q_OBJECT

    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double leftValue READ getLeftValue WRITE setLeftValue)
    Q_PROPERTY(double rightValue READ getRightValue WRITE setRightValue)

    Q_PROPERTY(QColor colorBg READ getColorBg WRITE setColorBg)
    Q_PROPERTY(QColor colorValue READ getColorValue WRITE setColorValue)
    Q_PROPERTY(QColor colorLow READ getColorLow WRITE setColorLow)
    Q_PROPERTY(QColor colorHigh READ getColorHigh WRITE setColorHigh)

public:
    explicit BarVUMeter(QWidget *parent = 0);
    ~BarVUMeter();

protected:
    void paintEvent(QPaintEvent *);
    void drawBorder(QPainter *painter);
    void drawBar(QPainter *painter);
    void drawValue(QPainter *painter);

private:
    double minValue;        //最小值
    double maxValue;        //最大值
    double leftValue;       //左边值
    double rightValue;      //右边值

    QColor colorBg;         //背景颜色
    QColor colorValue;      //值颜色
    QColor colorHigh;       //大值颜色
    QColor colorLow;        //小值颜色

public:
    double getMinValue()    const;
    double getMaxValue()    const;
    double getLeftValue()   const;
    double getRightValue()  const;

    QColor getColorBg()     const;
    QColor getColorValue()  const;
    QColor getColorLow()    const;
    QColor getColorHigh()   const;

    QSize sizeHint()        const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    //设置最小值最大值
    void setMinValue(double minValue);
    void setMaxValue(double maxValue);
    //设置左通道右通道音量值
    void setLeftValue(double leftValue);
    void setRightValue(double rightValue);

    //设置背景颜色
    void setColorBg(const QColor &colorBg);
    //设置值进度颜色
    void setColorValue(const QColor &colorValue);
    //设置大值颜色
    void setColorHigh(const QColor &colorHigh);
    //设置小值颜色
    void setColorLow(const QColor &colorLow);

Q_SIGNALS:
    //左通道音量值改变
    void valueLChanged(double);
    //右通道音量值改变
    void valueRChanged(double);
};

#endif
