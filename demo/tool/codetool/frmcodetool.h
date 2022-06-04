#ifndef FRMCODETOOL_H
#define FRMCODETOOL_H

#include <QWidget>

namespace Ui {
class frmCodeTool;
}

class frmCodeTool : public QWidget
{
    Q_OBJECT

public:
    explicit frmCodeTool(QWidget *parent = 0);
    ~frmCodeTool();

private:
    Ui::frmCodeTool *ui;

private:
    void newHeader(const QString &fileName);
    void newSource(const QString &fileName);

private slots:
    void on_btnSelect_clicked();
    void on_btnDo_clicked();
};

#endif // FRMCODETOOL_H
