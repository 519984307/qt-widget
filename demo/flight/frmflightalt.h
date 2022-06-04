#ifndef FRMFLIGHTALT_H
#define FRMFLIGHTALT_H

#include <QWidget>

namespace Ui {
class frmFlightALT;
}

class frmFlightALT : public QWidget
{
    Q_OBJECT

public:
    explicit frmFlightALT(QWidget *parent = 0);
    ~frmFlightALT();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::frmFlightALT *ui;

private slots:
    void initForm();
    void on_sliderAltitude_valueChanged(int value);
    void on_sliderPressure_valueChanged(int value);
};

#endif // FRMFLIGHTALT_H
