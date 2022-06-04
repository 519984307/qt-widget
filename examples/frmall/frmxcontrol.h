#ifndef FRMXCONTROL_H
#define FRMXCONTROL_H

#include <QWidget>

namespace Ui {
class frmXControl;
}

class frmXControl : public QWidget
{
    Q_OBJECT

public:
    explicit frmXControl(QWidget *parent = 0);
    ~frmXControl();

private:
    Ui::frmXControl *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMXCONTROL_H
