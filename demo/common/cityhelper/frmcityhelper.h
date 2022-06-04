#ifndef FRMCITYHELPER_H
#define FRMCITYHELPER_H

#include <QWidget>
class QListWidgetItem;

namespace Ui {
class frmCityHelper;
}

class frmCityHelper : public QWidget
{
    Q_OBJECT

public:
    explicit frmCityHelper(QWidget *parent = 0);
    ~frmCityHelper();

private:
    Ui::frmCityHelper *ui;

private slots:
    void initForm();
    void on_cboxProvince_currentIndexChanged(int);
    void on_cboxCity_currentIndexChanged(int);
    void on_listProvince_currentItemChanged(QListWidgetItem *, QListWidgetItem *);
    void on_listCity_currentItemChanged(QListWidgetItem *, QListWidgetItem *);
};

#endif // FRMCITYHELPER_H
