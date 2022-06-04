#ifndef FRMYLISTWIDGET_H
#define FRMYLISTWIDGET_H

#include <QWidget>

namespace Ui {
class frmYListWidget;
}

class frmYListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmYListWidget(QWidget *parent = 0);
    ~frmYListWidget();

private:
    Ui::frmYListWidget *ui;
};

#endif // FRMYLISTWIDGET_H
