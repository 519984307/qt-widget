#ifndef FRMYSPINBOX_H
#define FRMYSPINBOX_H

#include <QWidget>

namespace Ui {
class frmYSpinBox;
}

class frmYSpinBox : public QWidget
{
    Q_OBJECT

public:
    explicit frmYSpinBox(QWidget *parent = 0);
    ~frmYSpinBox();

private:
    Ui::frmYSpinBox *ui;
};

#endif // FRMYSPINBOX_H
