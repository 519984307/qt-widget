#ifndef FRMCODECOUNT_H
#define FRMCODECOUNT_H

#include <QWidget>

namespace Ui {
class frmCodeCount;
}

class frmCodeCount : public QWidget
{
    Q_OBJECT

public:
    explicit frmCodeCount(QWidget *parent = 0);
    ~frmCodeCount();

private:
    Ui::frmCodeCount *ui;
    QStringList listFile;

private:
    void initForm();
    bool checkFile(const QString &fileName);
    void countCode(const QString &filePath);
    void countCode(const QStringList &files);
    void countCode(const QString &fileName, int &lineCode, int &lineBlank, int &lineNotes);

private slots:
    void on_btnOpenFile_clicked();
    void on_btnOpenPath_clicked();
    void on_btnClear_clicked();
};

#endif // FRMCODECOUNT_H
