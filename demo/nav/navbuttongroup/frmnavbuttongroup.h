#ifndef FRMNAVBUTTONGROUP_H
#define FRMNAVBUTTONGROUP_H

#include <QWidget>

namespace Ui {
class frmNavButtonGroup;
}

class frmNavButtonGroup : public QWidget
{
    Q_OBJECT

public:
    explicit frmNavButtonGroup(QWidget *parent = 0);
    ~frmNavButtonGroup();

private:
    Ui::frmNavButtonGroup *ui;

private slots:
    void initForm();
    void setIndex();
};

#endif // FRMNAVBUTTONGROUP_H
