#ifndef FRMPROGRESSCOUNTDOWN_H
#define FRMPROGRESSCOUNTDOWN_H

#include <QWidget>

namespace Ui {
class frmProgressCountDown;
}

class frmProgressCountDown : public QWidget
{
    Q_OBJECT

public:
    explicit frmProgressCountDown(QWidget *parent = 0);
    ~frmProgressCountDown();

private:
    Ui::frmProgressCountDown *ui;

private slots:
    void initForm();
};

#endif // FRMPROGRESSCOUNTDOWN_H
