#ifndef FRMGAUGECOMPASSPAN_H
#define FRMGAUGECOMPASSPAN_H

#include <QWidget>

namespace Ui {
class frmGaugeCompassPan;
}

class frmGaugeCompassPan : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeCompassPan(QWidget *parent = 0);
    ~frmGaugeCompassPan();

private:
    Ui::frmGaugeCompassPan *ui;
    int precision;

private slots:
    void initForm();
    void on_horizontalSlider_valueChanged(int value);
};

#endif // FRMGAUGECOMPASSPAN_H
