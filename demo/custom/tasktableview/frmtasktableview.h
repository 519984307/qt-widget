#ifndef FRMTASKTABLEVIEW_H
#define FRMTASKTABLEVIEW_H

#include <QWidget>

namespace Ui {
class frmTaskTableView;
}

class frmTaskTableView : public QWidget
{
	Q_OBJECT

public:
    frmTaskTableView(QWidget *parent = 0);
    ~frmTaskTableView();

private:
    Ui::frmTaskTableView *ui;

private slots:
	void initForm();
    void clicked();
};

#endif // FRMTASKTABLEVIEW_H
