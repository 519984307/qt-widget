#ifndef FRMFLIGHTADI_H
#define FRMFLIGHTADI_H

#include <QWidget>

namespace Ui {
class frmFlightADI;
}

class frmFlightADI : public QWidget
{
    Q_OBJECT

public:
    explicit frmFlightADI(QWidget *parent = 0);
    ~frmFlightADI();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::frmFlightADI *ui;

private slots:
    void initForm();
    void on_sliderRoll_valueChanged(int value);
    void on_sliderPitch_valueChanged(int value);
};

#endif // FRMFLIGHTADI_H
