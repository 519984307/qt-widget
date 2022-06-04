#ifndef FRMPROGRESSARC_H
#define FRMPROGRESSARC_H

#include <QWidget>

namespace Ui {
class frmProgressArc;
}

class frmProgressArc : public QWidget
{
    Q_OBJECT

public:
    explicit frmProgressArc(QWidget *parent = 0);
    ~frmProgressArc();

private:
    Ui::frmProgressArc *ui;

private slots:
    void initForm();

};

#endif // FRMPROGRESSARC_H
