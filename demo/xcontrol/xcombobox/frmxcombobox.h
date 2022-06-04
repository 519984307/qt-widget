#ifndef FRMXCOMBOBOX_H
#define FRMXCOMBOBOX_H

#include <QWidget>

namespace Ui {
class frmXComboBox;
}

class frmXComboBox : public QWidget
{
    Q_OBJECT

public:
    explicit frmXComboBox(QWidget *parent = 0);
    ~frmXComboBox();

private:
    Ui::frmXComboBox *ui;

private slots:
    void initForm();
};

#endif // FRMXCOMBOBOX_H
