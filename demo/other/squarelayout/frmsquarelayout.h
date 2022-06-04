#ifndef FRMSQUARELAYOUT_H
#define FRMSQUARELAYOUT_H

#include <QWidget>

namespace Ui {
class frmSquareLayout;
}

class frmSquareLayout : public QWidget
{
    Q_OBJECT

public:
    explicit frmSquareLayout(QWidget *parent = 0);
    ~frmSquareLayout();

private:
    Ui::frmSquareLayout *ui;

private slots:
    void initForm();
};

#endif // FRMSQUARELAYOUT_H
