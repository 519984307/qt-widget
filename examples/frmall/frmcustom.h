#ifndef FRMCUSTOM_H
#define FRMCUSTOM_H

#include <QWidget>

namespace Ui {
class frmCustom;
}

class frmCustom : public QWidget
{
    Q_OBJECT

public:
    explicit frmCustom(QWidget *parent = 0);
    ~frmCustom();

private:
    Ui::frmCustom *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMCUSTOM_H
