#ifndef FRMMAGICPENGUIN_H
#define FRMMAGICPENGUIN_H

#include <QWidget>

namespace Ui {
class frmMagicPenguin;
}

class frmMagicPenguin : public QWidget
{
    Q_OBJECT

public:
    explicit frmMagicPenguin(QWidget *parent = 0);
    ~frmMagicPenguin();

private:
    Ui::frmMagicPenguin *ui;

private slots:
    void initForm();
};

#endif // FRMMAGICPENGUIN_H
