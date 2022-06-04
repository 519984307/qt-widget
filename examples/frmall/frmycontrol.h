#ifndef FRMYCONTROL_H
#define FRMYCONTROL_H

#include <QWidget>

namespace Ui {
class frmYControl;
}

class frmYControl : public QWidget
{
    Q_OBJECT

public:
    explicit frmYControl(QWidget *parent = 0);
    ~frmYControl();

private:
    Ui::frmYControl *ui;

private slots:
    void initForm();    

public slots:
    void setIndex(int index);
};

#endif // FRMYCONTROL_H
