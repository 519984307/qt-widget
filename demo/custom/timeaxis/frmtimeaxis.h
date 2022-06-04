#ifndef FRMTIMEAXIS_H
#define FRMTIMEAXIS_H

#include <QWidget>

namespace Ui {
class frmTimeAxis;
}

class frmTimeAxis : public QWidget
{
    Q_OBJECT

public:
    explicit frmTimeAxis(QWidget *parent = 0);
    ~frmTimeAxis();

private:
    Ui::frmTimeAxis *ui;

private slots:
    void initForm();
};

#endif // FRMTIMEAXIS_H
