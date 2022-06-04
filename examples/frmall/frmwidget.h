#ifndef FRMWIDGET_H
#define FRMWIDGET_H

#include <QWidget>

namespace Ui {
class frmWidget;
}

class frmWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmWidget(QWidget *parent = 0);
    ~frmWidget();

private:
    Ui::frmWidget *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMWIDGET_H
