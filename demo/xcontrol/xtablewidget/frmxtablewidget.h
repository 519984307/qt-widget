#ifndef FRMXTABLEWIDGET_H
#define FRMXTABLEWIDGET_H

#include <QWidget>

namespace Ui {
class frmXTableWidget;
}

class frmXTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmXTableWidget(QWidget *parent = 0);
    ~frmXTableWidget();

private:
    Ui::frmXTableWidget *ui;

private slots:
    void initForm();
};

#endif // FRMXTABLEWIDGET_H
