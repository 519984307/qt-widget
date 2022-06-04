#ifndef FRMYTREEWIDGET_H
#define FRMYTREEWIDGET_H

#include <QWidget>

namespace Ui {
class frmYTreeWidget;
}

class frmYTreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmYTreeWidget(QWidget *parent = 0);
    ~frmYTreeWidget();

private:
    Ui::frmYTreeWidget *ui;

private slots:
    void initForm();
};

#endif // FRMYTREEWIDGET_H
