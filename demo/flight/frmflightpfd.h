#ifndef FRMFLIGHTPFD_H
#define FRMFLIGHTPFD_H

#include <QWidget>

namespace Ui {
class frmFlightPFD;
}

class frmFlightPFD : public QWidget
{
    Q_OBJECT

public:
    explicit frmFlightPFD(QWidget *parent = 0);
    ~frmFlightPFD();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::frmFlightPFD *ui;

private slots:
    void initForm();
    void on_sliderRoll_valueChanged(int value);
    void on_sliderPitch_valueChanged(int value);
    void on_sliderAltitude_valueChanged(int value);
    void on_sliderHeading_valueChanged(int value);
    void on_sliderAirspeed_valueChanged(int value);
    void on_sliderDistance_valueChanged(int value);
};

#endif // FRMFLIGHTPFD_H
