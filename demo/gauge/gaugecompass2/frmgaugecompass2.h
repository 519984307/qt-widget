#ifndef FRMGAUGECOMPASS2_H
#define FRMGAUGECOMPASS2_H

#include <QWidget>

namespace Ui {
class frmGaugeCompass2;
}

class frmGaugeCompass2 : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeCompass2(QWidget *parent = 0);
    ~frmGaugeCompass2();

private:
    Ui::frmGaugeCompass2 *ui;

private slots:
    void initForm();
};

#endif // FRMGAUGECOMPASS2_H
