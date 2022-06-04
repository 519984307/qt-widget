#ifndef FRMFLIGHTVSI_H
#define FRMFLIGHTVSI_H

#include <QWidget>

namespace Ui {
class frmFlightVSI;
}

class frmFlightVSI : public QWidget
{
    Q_OBJECT

public:
    explicit frmFlightVSI(QWidget *parent = 0);
    ~frmFlightVSI();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::frmFlightVSI *ui;

private slots:
    void initForm();
    void on_sliderClimbRate_valueChanged(int value);
};

#endif // FRMFLIGHTVSI_H
