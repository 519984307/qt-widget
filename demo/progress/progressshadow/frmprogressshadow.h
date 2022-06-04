#ifndef FRMPROGRESSSHADOW_H
#define FRMPROGRESSSHADOW_H

#include <QWidget>

namespace Ui {
class frmProgressShadow;
}

class frmProgressShadow : public QWidget
{
    Q_OBJECT

public:
    explicit frmProgressShadow(QWidget *parent = 0);
    ~frmProgressShadow();

private:
    Ui::frmProgressShadow *ui;

private slots:
    void initForm();
};

#endif // FRMPROGRESSSHADOW_H
