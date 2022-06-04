#ifndef FRMSHADOWCALENDAR_H
#define FRMSHADOWCALENDAR_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class frmShadowCalendar;
}

class frmShadowCalendar : public QWidget
{
    Q_OBJECT

public:
    explicit frmShadowCalendar(QWidget *parent = 0);
    ~frmShadowCalendar();

private:
    Ui::frmShadowCalendar *ui;
    QDateTime currentDate;

private slots:
    void initForm();
    void updateInfo();

private slots:
    void on_btnUp_clicked();
    void on_btnDown_clicked();
};

#endif // FRMSHADOWCALENDAR_H
