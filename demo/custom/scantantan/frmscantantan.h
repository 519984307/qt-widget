#ifndef FRMSCANTANTAN_H
#define FRMSCANTANTAN_H

#include <QWidget>

namespace Ui {
class frmScanTanTan;
}

class frmScanTanTan : public QWidget
{
    Q_OBJECT

public:
    explicit frmScanTanTan(QWidget *parent = 0);
    ~frmScanTanTan();

private:
    Ui::frmScanTanTan *ui;

private slots:
    void initForm();
};

#endif // FRMSCANTANTAN_H
