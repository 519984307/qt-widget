#ifndef FRMWAVEWATER_H
#define FRMWAVEWATER_H

#include <QWidget>

namespace Ui {
class frmWaveWater;
}

class frmWaveWater : public QWidget
{
    Q_OBJECT

public:
    explicit frmWaveWater(QWidget *parent = 0);
    ~frmWaveWater();

private:
    Ui::frmWaveWater *ui;

private slots:
    void initForm();
    void loadImage(const QString &file);
    void on_btnOpen_clicked();
};

#endif // FRMWAVEWATER_H
