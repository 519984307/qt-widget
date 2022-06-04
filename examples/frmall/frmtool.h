#ifndef FRMTOOL_H
#define FRMTOOL_H

#include <QWidget>

namespace Ui {
class frmTool;
}

class frmTool : public QWidget
{
    Q_OBJECT

public:
    explicit frmTool(QWidget *parent = 0);
    ~frmTool();

private:
    Ui::frmTool *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMTOOL_H
