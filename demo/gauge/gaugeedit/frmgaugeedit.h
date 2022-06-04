#ifndef FRMGAUGEEDIT_H
#define FRMGAUGEEDIT_H

#include <QWidget>

namespace Ui {
class frmGaugeEdit;
}

class frmGaugeEdit : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeEdit(QWidget *parent = 0);
    ~frmGaugeEdit();

private:
    Ui::frmGaugeEdit *ui;

private slots:
    void initForm();
};

#endif // FRMGAUGEEDIT_H
