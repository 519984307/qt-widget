#ifndef FRMFLIGHT_H
#define FRMFLIGHT_H

#include <QWidget>

namespace Ui {
class frmFlight;
}

class frmFlight : public QWidget
{
    Q_OBJECT

public:
    explicit frmFlight(QWidget *parent = 0);
    ~frmFlight();

private:
    Ui::frmFlight *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMFLIGHT_H
