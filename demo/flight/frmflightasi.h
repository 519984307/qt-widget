#ifndef FRMFLIGHTASI_H
#define FRMFLIGHTASI_H

#include <QWidget>

namespace Ui {
class frmFlightASI;
}

class frmFlightASI : public QWidget
{
    Q_OBJECT

public:
    explicit frmFlightASI(QWidget *parent = 0);
    ~frmFlightASI();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::frmFlightASI *ui;

private slots:
    void initForm();
    void on_sliderAirspeed_valueChanged(int value);
};

#endif // FRMFLIGHTASI_H
