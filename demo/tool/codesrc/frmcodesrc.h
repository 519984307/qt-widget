#ifndef FRMCODESRC_H
#define FRMCODESRC_H

#include <QWidget>
class QListWidgetItem;

namespace Ui {
class frmCodeSrc;
}

class frmCodeSrc : public QWidget
{
    Q_OBJECT

public:
    explicit frmCodeSrc(QWidget *parent = 0);
    ~frmCodeSrc();

private:
    Ui::frmCodeSrc *ui;
    QStringList fileNames;

private slots:
    void initForm();
    void getFileNames(const QString &path);
    void on_btnSelect_clicked();
    void on_btnCopy_clicked();

    void on_btnSelectAll_clicked();
    void on_btnSelectNo_clicked();
    void on_btnSelectModel1_clicked();
    void on_btnSelectModel2_clicked();

    void on_txtPathSrc_textChanged(const QString &arg1);
    void on_listWidget_itemPressed(QListWidgetItem *item);
};

#endif // FRMCODESRC_H
