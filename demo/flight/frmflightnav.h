#ifndef FRMFLIGHTNAV_H
#define FRMFLIGHTNAV_H

#include <QWidget>

namespace Ui {
class frmFlightNAV;
}

class frmFlightNAV : public QWidget
{
    Q_OBJECT

public:
    explicit frmFlightNAV(QWidget *parent = 0);
    ~frmFlightNAV();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::frmFlightNAV *ui;

private slots:
    void initForm();
    void on_sliderHeading_valueChanged(int value);
    void on_sliderHeadingBug_valueChanged(int value);
    void on_sliderCourse_valueChanged(int value);
    void on_sliderBearing_valueChanged(int value);
    void on_sliderDeviation_valueChanged(int value);
    void on_sliderDistance_valueChanged(int value);
};

#endif // FRMFLIGHTNAV_H
