#ifndef SPIDERCHART_H
#define SPIDERCHART_H

/**
 * 蜘蛛网图控件 作者:东门吹雪(QQ:709102202) 整理:feiyangqingyun(QQ:517216493) 2022-03-02
 * 1. 可设置最大值最小值范围值。
 * 2. 可设置层级数量。
 * 3. 可设置边数量。
 * 4. 可设置边宽度。
 * 5. 可设置边颜色。
 * 6. 可设置边描述（种类）。
 * 7. 可设置开始角度。
 * 8. 可设置标尺位置。
 * 9. 可设置标尺可见。
 * 10. 可设置图例可见。
 * 11. 可设置线条宽度。
 * 12. 可设置线条颜色。
 * 13. 可设置文字颜色。
 */

#include <QWidget>
#include <QMap>
#include <QVector>

//重新定义一些数据类型
typedef QMap<QString, QVector<float> > mdata;
typedef QMap<QString, QColor> mcolor;

#ifdef quc
class Q_DECL_EXPORT SpiderChart : public QWidget
#else
class SpiderChart : public QWidget
#endif

{
    Q_OBJECT

    Q_PROPERTY(qreal minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(qreal maxValue READ getMaxValue WRITE setMaxValue)

    Q_PROPERTY(int levelCount READ getLevelCount WRITE setLevelCount)
    Q_PROPERTY(int sideCount READ getSideCount WRITE setSideCount)
    Q_PROPERTY(QColor sideColor READ getSideColor WRITE setSideColor)
    Q_PROPERTY(QString sideText READ getSideText WRITE setSideText)

    Q_PROPERTY(qreal startAngle READ getStartAngle WRITE setStartAngle)
    Q_PROPERTY(int scalePos READ getScalePos WRITE setScalePos)
    Q_PROPERTY(bool scaleVisible READ getScaleVisible WRITE setScaleVisible)
    Q_PROPERTY(bool legendVisible READ getLegendVisible WRITE setLegendVisible)

    Q_PROPERTY(qreal lineWidth READ getLineWidth WRITE setLineWidth)
    Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)

public:
    explicit SpiderChart(QWidget *parent = 0);
    ~SpiderChart();

protected:
    void paintEvent(QPaintEvent *);
    void drawSide(QPainter *painter);
    void drawLine(QPainter *painter);
    void drawText(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawValue(QPainter *painter);
    void drawLegend(QPainter *painter);

private:
    qreal minValue;             //最小值
    qreal maxValue;             //最大值

    int levelCount;             //层级数量
    int sideCount;              //边数量
    QColor sideColor;           //边颜色
    QString sideText;           //边描述(种类)

    int startAngle;             //开始角度
    int scalePos;               //标尺位置
    bool scaleVisible;          //标尺可见
    bool legendVisible;         //图例可见

    qreal lineWidth;            //线条宽度
    QColor lineColor;           //线条颜色
    QColor textColor;           //文字颜色

    int radius;                 //绘制半径
    double radiusPer;           //半径因子
    double startRad;            //开始弧度
    double deltaRad;            //三角弧度

    mdata dataValue;            //数据值集合
    mcolor dataColor;           //数据颜色集合

public:
    qreal getMinValue()         const;
    qreal getMaxValue()         const;

    int getLevelCount()         const;
    int getSideCount()          const;
    QColor getSideColor()       const;
    QString getSideText()       const;

    int getStartAngle()         const;
    int getScalePos()           const;
    bool getScaleVisible()      const;
    bool getLegendVisible()     const;

    qreal getLineWidth()        const;
    QColor getLineColor()       const;
    QColor getTextColor()       const;

    QSize sizeHint()            const;
    QSize minimumSizeHint()     const;

public Q_SLOTS:
    //设置最小值最大值范围值
    void setMinValue(qreal minValue);
    void setMaxValue(qreal maxValue);
    void setRange(qreal minValue, qreal maxValue);

    //设置层级数量+边数量+边颜色+种类描述
    void setLevelCount(int levelCount);
    void setSideCount(int sideCount);
    void setSideColor(const QColor &sideColor);
    void setSideText(const QString &sideText);

    //设置开始角度+标尺位置+标尺可见+图例可见
    void setStartAngle(int startAngle);
    void setScalePos(int scalePos);
    void setScaleVisible(bool scaleVisible);
    void setLegendVisible(bool legendVisible);

    //设置线条宽度+线条颜色+文字颜色
    void setLineWidth(qreal lineWidth);
    void setLineColor(const QColor &lineColor);
    void setTextColor(const QColor &textColor);

    //添加一项数据集合
    void addData(const QString &name, const QVector<float> &data, const QColor &color);
    //设置数据颜色
    void setDataColor(const QString &name, const QColor &color);
    //移除数据项
    void removeData(const QString &name);
    //清空所有数据
    void clearData();
};

#endif // SPIDERCHART_H
