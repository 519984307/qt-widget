#ifndef FRMEXAMPLESSIMPLE_H
#define FRMEXAMPLESSIMPLE_H

#include <QWidget>

namespace Ui {
class frmExamplesSimple;
}

class frmExamplesSimple : public QWidget
{
    Q_OBJECT

public:
    explicit frmExamplesSimple(QWidget *parent = 0);
    ~frmExamplesSimple();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::frmExamplesSimple *ui;

    //透明背景图片
    QPixmap bgPix;
    //所有控件名称集合
    QStringList listName;
    //要插入导航栏的控件名称集合
    QStringList listItem;

private slots:
    //初始化界面
    void initForm();

    //插入元素到左侧导航控件
    void addItem();
    //传入父类名称插入子类名称集合
    void addItem(const QString &parentName, const QStringList &childNames);

    //左侧导航按下对应的名称
    void pressed(const QString &childText, const QString &parentText);
};

#endif // FRMEXAMPLESSIMPLE_H
