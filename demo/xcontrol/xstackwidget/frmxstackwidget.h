#ifndef FRMXSTACKWIDGET_H
#define FRMXSTACKWIDGET_H

#include <QWidget>

namespace Ui {
class frmXStackWidget;
}

class frmXStackWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmXStackWidget(QWidget *parent = 0);
    ~frmXStackWidget();

private:
    Ui::frmXStackWidget *ui;

private slots:
    void initForm();    
};

#endif // FRMXSTACKWIDGET_H
