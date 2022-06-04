#ifndef FRMYTABWIDGET_H
#define FRMYTABWIDGET_H

#include <QWidget>

namespace Ui {
class frmYTabWidget;
}

class frmYTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmYTabWidget(QWidget *parent = 0);
    ~frmYTabWidget();

private:
    Ui::frmYTabWidget *ui;
};

#endif // FRMYTABWIDGET_H
