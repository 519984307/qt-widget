#ifndef FRMNAVPAGE_H
#define FRMNAVPAGE_H

#include <QWidget>

namespace Ui {
class frmNavPage;
}

class frmNavPage : public QWidget
{
    Q_OBJECT

public:
    explicit frmNavPage(QWidget *parent = 0);
    ~frmNavPage();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::frmNavPage *ui;

private slots:
    void initForm();
};

#endif // FRMNAVPAGE_H
