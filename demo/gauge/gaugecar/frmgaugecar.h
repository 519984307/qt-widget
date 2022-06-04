#ifndef FRMGAUGECAR_H
#define FRMGAUGECAR_H

#include <QWidget>
class QPropertyAnimation;

namespace Ui {
class frmGaugeCar;
}

class frmGaugeCar : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeCar(QWidget *parent = 0);
    ~frmGaugeCar();

private:
    Ui::frmGaugeCar *ui;
    QPropertyAnimation *animation;

private slots:
    void initForm();

private slots:
    void on_cboxPieStyle_currentIndexChanged(int index);
    void on_cboxPointerStyle_currentIndexChanged(int index);
    void on_horizontalSlider_valueChanged(int value);
    void on_cboxAnimationType_currentIndexChanged(int index);
};

#endif // FRMGAUGECAR_H
