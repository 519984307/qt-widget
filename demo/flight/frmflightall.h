#ifndef FRMFLIGHTALL_H
#define FRMFLIGHTALL_H

#include <QWidget>

namespace Ui {
class frmFlightAll;
}

class frmFlightAll : public QWidget
{
    Q_OBJECT

public:
    explicit frmFlightAll(QWidget *parent = 0);
    ~frmFlightAll();

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:
    Ui::frmFlightAll *ui;
    QTimer *timer;

private slots:
    void initForm();
    void testData();
    void addValue(int &value, bool &add, int min, int max, int step = 1);
};

#endif // FRMFLIGHTALL_H
