#ifndef FRMPROGRESSTIP_H
#define FRMPROGRESSTIP_H

#include <QWidget>

namespace Ui {
class frmProgressTip;
}

class frmProgressTip : public QWidget
{
    Q_OBJECT

public:
    explicit frmProgressTip(QWidget *parent = 0);
    ~frmProgressTip();

private:
    Ui::frmProgressTip *ui;

private slots:
    void initForm();
};

#endif // FRMPROGRESSTIP_H
