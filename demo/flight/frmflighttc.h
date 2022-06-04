#ifndef FRMFLIGHTTC_H
#define FRMFLIGHTTC_H

#include <QWidget>

namespace Ui {
class frmFlightTC;
}

class frmFlightTC : public QWidget
{
    Q_OBJECT

public:
    explicit frmFlightTC(QWidget *parent = 0);
    ~frmFlightTC();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::frmFlightTC *ui;

private slots:
    void initForm();
    void on_sliderTurnRate_valueChanged(int value);
    void on_sliderSlipSkid_valueChanged(int value);
};

#endif // FRMFLIGHTTC_H
