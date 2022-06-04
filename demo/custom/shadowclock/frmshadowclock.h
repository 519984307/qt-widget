#ifndef FRMSHADOWCLOCK_H
#define FRMSHADOWCLOCK_H

#include <QWidget>

namespace Ui {
class frmShadowClock;
}

class frmShadowClock : public QWidget
{
    Q_OBJECT

public:
    explicit frmShadowClock(QWidget *parent = 0);
    ~frmShadowClock();

private:
    Ui::frmShadowClock *ui;

private slots:
    void initForm();
};

#endif // FRMSHADOWCLOCK_H
