#ifndef FRMCODECLEAN_H
#define FRMCODECLEAN_H

#include <QWidget>

namespace Ui {
class frmCodeClean;
}

class frmCodeClean : public QWidget
{
    Q_OBJECT

public:
    explicit frmCodeClean(QWidget *parent = 0);
    ~frmCodeClean();

private:
    Ui::frmCodeClean *ui;

private slots:
    void on_btnSelect_clicked();
    void on_btnDo_clicked();
};

#endif // FRMCODECLEAN_H
