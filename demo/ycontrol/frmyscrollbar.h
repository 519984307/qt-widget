#ifndef FRMYSCROLLBAR_H
#define FRMYSCROLLBAR_H

#include <QWidget>

namespace Ui {
class frmYScrollBar;
}

class frmYScrollBar : public QWidget
{
    Q_OBJECT

public:
    explicit frmYScrollBar(QWidget *parent = 0);
    ~frmYScrollBar();

private:
    Ui::frmYScrollBar *ui;
};

#endif // FRMYSCROLLBAR_H
