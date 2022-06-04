#ifndef FRMTIMELINE_H
#define FRMTIMELINE_H

#include <QWidget>

namespace Ui {
class frmTimeLine;
}

class frmTimeLine : public QWidget
{
    Q_OBJECT

public:
    explicit frmTimeLine(QWidget *parent = 0);
    ~frmTimeLine();

private:
    Ui::frmTimeLine *ui;

private slots:
    void initForm();
};

#endif // FRMTIMELINE_H
