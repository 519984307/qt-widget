#ifndef FRMSPIDERCHART_H
#define FRMSPIDERCHART_H

#include <QWidget>

namespace Ui {
class frmSpiderChart;
}

class frmSpiderChart : public QWidget
{
    Q_OBJECT

public:
    explicit frmSpiderChart(QWidget *parent = 0);
    ~frmSpiderChart();

private:
    Ui::frmSpiderChart *ui;

private slots:
    void initForm();
    void on_btnAdd_clicked();
    void on_sboxLevelCount_valueChanged(int arg1);
    void on_sboxSideCount_valueChanged(int arg1);
};

#endif // FRMSPIDERCHART_H
