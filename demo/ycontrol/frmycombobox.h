#ifndef FRMYCOMBOBOX_H
#define FRMYCOMBOBOX_H

#include <QWidget>

namespace Ui {
class frmYComboBox;
}

class frmYComboBox : public QWidget
{
    Q_OBJECT

public:
    explicit frmYComboBox(QWidget *parent = 0);
    ~frmYComboBox();

private:
    Ui::frmYComboBox *ui;
};

#endif // FRMYCOMBOBOX_H
