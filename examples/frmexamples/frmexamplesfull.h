#ifndef FRMEXAMPLESFULL_H
#define FRMEXAMPLESFULL_H

#include <QWidget>

namespace Ui {
class frmExamplesFull;
}

class frmExamplesFull : public QWidget
{
    Q_OBJECT

public:
    explicit frmExamplesFull(QWidget *parent = 0);
    ~frmExamplesFull();

protected:
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
    void paintEvent(QPaintEvent *);

private:
    Ui::frmExamplesFull *ui;

    //是否需要绘制透明背景
    bool needDraw;
    //需要绘制透明背景的控件
    QStringList listDraw;
    //透明背景图片
    QPixmap bgPix;

    //控件分组名称
    QStringList listParent;
    //要插入导航栏的控件名称集合
    QStringList listItem;

    //控件分组下的控件名称集合
    QList<QStringList> listChilds;
    //控件分组对应堆栈窗体集合
    QList<QWidget *> widgets;

private slots:
    //初始化界面
    void initForm();
    //初始化堆栈窗体
    void initWidget();
    //初始化控件分组名称
    void initParent();
    //初始化分组下的控件名称
    void initChild();

    //插入元素到左侧导航控件
    void addItem();
    //传入父类名称插入子类名称集合
    void addItem(const QString &parentName, const QStringList &childNames);

    //左侧导航按下对应的名称
    void pressed(const QString &childText, const QString &parentText);
};

#endif // FRMEXAMPLESFULL_H
