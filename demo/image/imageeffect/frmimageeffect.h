#ifndef FRMIMAGEEFFECT_H
#define FRMIMAGEEFFECT_H

#include <QWidget>

namespace Ui {
class frmImageEffect;
}

class frmImageEffect : public QWidget
{
    Q_OBJECT

public:
    explicit frmImageEffect(QWidget *parent = 0);
    ~frmImageEffect();

protected:
    void showEvent(QShowEvent *);
    void resizeEvent(QResizeEvent *);

private:
    Ui::frmImageEffect *ui;

private slots:
    void initForm();
    void imageEffect();
    void on_btnOpen_clicked();
};

#endif // FRMIMAGEEFFECT_H
