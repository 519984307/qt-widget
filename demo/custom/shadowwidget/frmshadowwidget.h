#ifndef FRMSHADOWWIDGET_H
#define FRMSHADOWWIDGET_H

#include <QWidget>

namespace Ui {
class frmShadowWidget;
}

class frmShadowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmShadowWidget(QWidget *parent = 0);
    ~frmShadowWidget();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::frmShadowWidget *ui;

private slots:
    void initForm();
    void on_btnChange_clicked();
    void on_btnShow_clicked();
};

#endif // FRMSHADOWWIDGET_H
