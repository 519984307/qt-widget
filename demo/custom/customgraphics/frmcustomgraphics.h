#ifndef FRMCUSTOMGRAPHICS_H
#define FRMCUSTOMGRAPHICS_H

#include <QWidget>

namespace Ui {
class frmCustomGraphics;
}

class frmCustomGraphics : public QWidget
{
    Q_OBJECT

public:
    explicit frmCustomGraphics(QWidget *parent = 0);
    ~frmCustomGraphics();

private:
    Ui::frmCustomGraphics *ui;

private slots:
    void receivePoints(const QVector<QPoint> &points);
    void on_btnOk_clicked();
};

#endif // FRMCUSTOMGRAPHICS_H
