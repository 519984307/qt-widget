#ifndef FRMCODECOPY_H
#define FRMCODECOPY_H

#include <QWidget>

namespace Ui {
class frmCodeCopy;
}

class frmCodeCopy : public QWidget
{
    Q_OBJECT

public:
    explicit frmCodeCopy(QWidget *parent = 0);
    ~frmCodeCopy();

private:
    Ui::frmCodeCopy *ui;
    QStringList deletePaths;
    QStringList deleteFiles;
    QStringList fileNames;

private slots:
    void clear();
    void on_btnSelectTarget_clicked();
    void on_btnSelectDesigner_clicked();
    void on_txtPathDesigner_textChanged(const QString &arg1);

    void getDeleteFiles(const QString &path);
    void getDeletePaths(const QString &path);
    void deleteFile(const QString &name);
    void deletePath(const QString &name);
    void getOtherPath();
    void on_btnDelete_clicked();

    void getFileNames(const QString &path);
    void copyFile(const QString &path, bool fileH, bool fileCpp);
    void copyFile(const QString &fileName, const QString &newName);
    void on_btnCopy_clicked();
    void on_btnDo_clicked();
};

#endif // FRMCODECOPY_H
