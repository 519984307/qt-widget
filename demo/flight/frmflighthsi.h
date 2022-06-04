#ifndef FRMFLIGHTHSI_H
#define FRMFLIGHTHSI_H

#include <QWidget>

namespace Ui {
class frmFlightHSI;
}

class frmFlightHSI : public QWidget
{
    Q_OBJECT

public:
    explicit frmFlightHSI(QWidget *parent = 0);
    ~frmFlightHSI();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::frmFlightHSI *ui;

private slots:
    void initForm();
    void on_sliderHeading_valueChanged(int value);
};

#endif // FRMFLIGHTHSI_H
