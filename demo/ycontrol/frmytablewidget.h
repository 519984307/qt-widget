#ifndef FRMYTABLEWIDGET_H
#define FRMYTABLEWIDGET_H

#include <QWidget>

namespace Ui {
class frmYTableWidget;
}

class frmYTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmYTableWidget(QWidget *parent = 0);
    ~frmYTableWidget();

private:
    Ui::frmYTableWidget *ui;

private slots:
    void initForm();
};

#endif // FRMYTABLEWIDGET_H
