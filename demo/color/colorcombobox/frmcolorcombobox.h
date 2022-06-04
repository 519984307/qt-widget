#ifndef FRMCOLORCOMBOBOX_H
#define FRMCOLORCOMBOBOX_H

#include <QWidget>

namespace Ui {
class frmColorComboBox;
}

class frmColorComboBox : public QWidget
{
    Q_OBJECT

public:
    explicit frmColorComboBox(QWidget *parent = 0);
    ~frmColorComboBox();

private:
    Ui::frmColorComboBox *ui;

private slots:
    void initForm();
};

#endif // FRMCOLORCOMBOBOX_H
