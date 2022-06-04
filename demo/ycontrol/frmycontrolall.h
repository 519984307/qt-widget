#ifndef FRMYCONTROLALL_H
#define FRMYCONTROLALL_H

#include <QWidget>

namespace Ui {
class frmYControlAll;
}

class frmYControlAll : public QWidget
{
    Q_OBJECT

public:
    explicit frmYControlAll(QWidget *parent = 0);
    ~frmYControlAll();

private:
    Ui::frmYControlAll *ui;

private slots:
    void initForm();
    void initTree();
    void initTable();
};

#endif // FRMYCONTROLALL_H
