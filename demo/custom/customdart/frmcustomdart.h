#ifndef FRMCUSTOMDART_H
#define FRMCUSTOMDART_H

#include <QWidget>

namespace Ui {
class frmCustomDart;
}

class frmCustomDart : public QWidget
{
    Q_OBJECT

public:
    explicit frmCustomDart(QWidget *parent = 0);
    ~frmCustomDart();

private:
    Ui::frmCustomDart *ui;

private slots:
    void initForm();
};

#endif // FRMCUSTOMDART_H
