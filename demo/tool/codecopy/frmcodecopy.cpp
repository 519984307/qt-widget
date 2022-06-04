#pragma execution_character_set("utf-8")

#include "frmcodecopy.h"
#include "ui_frmcodecopy.h"
#include "qlineedit.h"
#include "qfiledialog.h"
#include "qdatetime.h"
#include "qdir.h"
#include "qfile.h"
#include "qfileinfo.h"
#include "qmessagebox.h"
#include "qdebug.h"

#define TIMEMS QTime::currentTime().toString("hh:mm:ss zzz")

frmCodeCopy::frmCodeCopy(QWidget *parent) : QWidget(parent), ui(new Ui::frmCodeCopy)
{
    ui->setupUi(this);
}

frmCodeCopy::~frmCodeCopy()
{
    delete ui;
}

void frmCodeCopy::clear()
{
    deletePaths.clear();
    deleteFiles.clear();
    fileNames.clear();
    ui->txtHeader->clear();
    ui->txtSource->clear();
    ui->txtResult->clear();
}

void frmCodeCopy::on_btnSelectTarget_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    if (!path.isEmpty()) {
        ui->cboxPathTarget->lineEdit()->setText(path);
    }
}

void frmCodeCopy::on_btnSelectDesigner_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    if (!path.isEmpty()) {
        ui->txtPathDesigner->setText(path);
    }
}

void frmCodeCopy::on_txtPathDesigner_textChanged(const QString &arg1)
{
    ui->txtPathInclude->setText(arg1 + "/include");
}

void frmCodeCopy::getDeleteFiles(const QString &path)
{
    //统计目录下的文件
    QDir dir(path);
    if (!dir.exists()) {
        return;
    }

    QFileInfoList listInfo = dir.entryInfoList();
    foreach (QFileInfo fileInfo, listInfo) {
        QString fileName = fileInfo.fileName();
        if (fileInfo.isFile()) {
            if (fileName.endsWith(".pro.user")) {
                QString file = fileInfo.filePath();
                deleteFiles << file;
            }
        } else {
            if (fileName == "." || fileName == "..") {
                continue;
            }

            QString path = fileInfo.absoluteFilePath();
            getDeleteFiles(path);
        }
    }
}

void frmCodeCopy::getDeletePaths(const QString &path)
{
    //统计目录下的文件夹
    QDir dir(path);
    if (!dir.exists()) {
        return;
    }

    //只统计 build 开头和 bin 开头的 可以自行增加对应的目录
    QFileInfoList listInfo = dir.entryInfoList();
    foreach (QFileInfo fileInfo, listInfo) {
        QString fileName = fileInfo.fileName();
        if (fileName.contains("build-") || fileName.startsWith("bin")) {
            QString path = fileInfo.absoluteFilePath();
            deletePaths << path;
        }
    }
}

void frmCodeCopy::deleteFile(const QString &name)
{
    QFile(name).remove();
    QString msg = QString("%1 -> %2").arg(TIMEMS).arg(name);
    ui->txtSource->append(msg);
}

void frmCodeCopy::deletePath(const QString &name)
{
    QDir dir(name);
#if 0
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    //这个方法可以递归彻底删除文件夹 不管文件夹下是否有文件 比较暴力
    //此方法慎用 必须指定明确的文件夹 不然删除默认的目录哭都来不及 网上多个人中招
    dir.removeRecursively();
#endif
#else
    //循环遍历删除文件及文件夹
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList) {
        if (fi.isFile()) {
            fi.dir().remove(fi.fileName());
        } else {
            deletePath(fi.absoluteFilePath());
            dir.rmpath(fi.absoluteFilePath());
        }
    }
    //最后删除最外层的目录
    dir.rmpath(name);
#endif
    QString msg = QString("%1 -> %2").arg(TIMEMS).arg(name);
    ui->txtResult->append(msg);
}

void frmCodeCopy::getOtherPath()
{
    QStringList listPath;
    listPath << "I:/gitee/QWidgetDemo";
    listPath << "I:/github/QWidgetDemo";
    listPath << "H:/codeniubi/qui";
    foreach (QString path, listPath) {
        //找到根目录下的build+bin目录
        getDeletePaths(path);
        getDeleteFiles(path);
        //找到根目录下的目录
        QDir dir(path);
        QStringList paths = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
        //找到这些目录下的build+bin目录
        foreach (QString p, paths) {
            getDeletePaths(path + "/" + p);
        }
    }
}

void frmCodeCopy::on_btnDelete_clicked()
{
    this->clear();

    //目录不存在则不用处理
    QString pathTarget = ui->cboxPathTarget->currentText().trimmed();
    QDir dirTarget(pathTarget);
    if (!dirTarget.exists()) {
        return;
    }

    //先删除发布的目录
    deletePath(ui->txtPathInclude->text().trimmed());
    deletePath(ui->txtPathDesigner->text().trimmed() + "/temp");

    //找出所有要删除的文件
    getDeleteFiles(pathTarget);

    //删除主目录的pro.user文件
    QString pathQuc = "H:/codeniubi/quc";
    deleteFiles << pathQuc + "/quc.pro.user";
    deleteFiles << pathQuc + "/demo/demo.pro.user";
    deleteFiles << pathQuc + "/designer/designer.pro.user";
    deleteFiles << pathQuc + "/examples/examples.pro.user";

    //删除主目录下的build目录
    QDir dirQuc(pathQuc);
    QFileInfoList listInfo = dirQuc.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QFileInfo fileInfo, listInfo) {
        QString path = fileInfo.filePath();
        if (path.contains("build-")) {
            deletePaths << path;
        }
    }

    //找到demo文件夹下的bin目录+build目录
    listInfo = dirTarget.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QFileInfo fileInfo, listInfo) {
        //demo目录下的bin+build编译目录也加进去
        QString path = fileInfo.filePath();
        if (path.contains("build-") || path.contains("bin")) {
            deletePaths << path;
            continue;
        }

        getDeletePaths(path);
    }

    //查找其他的临时目录
    getOtherPath();

    int count = deleteFiles.count() + deletePaths.count();
    if (count <= 0) {
        return;
    }

    ui->progressBar->setRange(0, count);
    ui->progressBar->setValue(0);

    //逐个删除文件
    foreach (QString file, deleteFiles) {
        deleteFile(file);
        ui->progressBar->setValue(ui->progressBar->value() + 1);
    }

    //逐个删除目录
    foreach (QString path, deletePaths) {
        deletePath(path);
        ui->progressBar->setValue(ui->progressBar->value() + 1);
    }

    ui->progressBar->setValue(ui->progressBar->maximum());
    QMessageBox::information(this, "提示", "恭喜清理文件完成!");
}

void frmCodeCopy::getFileNames(const QString &path)
{
    //统计目录下的文件
    QDir dir(path);
    if (!dir.exists()) {
        QMessageBox::critical(this, "错误", "目录不存在请检查!");
        return;
    }

    QFileInfoList listInfo = dir.entryInfoList();
    foreach (QFileInfo fileInfo, listInfo) {
        QString fileName = fileInfo.fileName();
        if (fileInfo.isFile()) {
            if (fileName.startsWith("frm") || fileName == "main.cpp") {
                continue;
            }
            if (!fileName.endsWith(".h") && !fileName.endsWith(".cpp")) {
                continue;
            }

            QString file = fileInfo.filePath();
            fileNames << file;
        } else {
            if (fileName == "." || fileName == "..") {
                continue;
            }
            if (fileName.startsWith("build-")) {
                continue;
            }

            QString path = fileInfo.absoluteFilePath();
            getFileNames(path);
        }
    }
}

void frmCodeCopy::copyFile(const QString &path, bool fileH, bool fileCpp)
{
    this->clear();

    //从src目录下挨个拷贝文件到目录
    QString pathDesigner = ui->txtPathDesigner->text().trimmed();
    QString pathSrc = pathDesigner + "/src";
    QDir dirSrc(pathSrc);
    if (!dirSrc.exists()) {
        return;
    }

    //目录不存在则新建
    QDir dir(path);
    if (!dir.exists()) {
        dir.mkdir(path);
    }

    //找到src文件夹下的控件分组目录对应的所有控件源码文件
    getFileNames(pathSrc);
    if (fileNames.count() <= 0) {
        return;
    }

    ui->progressBar->setRange(0, fileNames.count());
    ui->progressBar->setValue(0);

    foreach (QString fileDesigner, fileNames) {
        //打印信息执行进度条
        QString msg = QString("%1 -> %2").arg(TIMEMS).arg(fileDesigner);
        ui->progressBar->setValue(ui->progressBar->value() + 1);

        //识别不同的文件夹 只拷贝头文件用于发布sdk
        if (fileDesigner.endsWith(".h") && fileH) {
            ui->txtHeader->append(msg);
            if (!fileH) {
                continue;
            }
        } else if (fileDesigner.endsWith(".cpp")) {
            ui->txtSource->append(msg);
            if (!fileCpp) {
                continue;
            }
        }

        QStringList list = fileDesigner.split("/");
        QString file = QString("%1/%2").arg(path).arg(list.last());
        copyFile(fileDesigner, file);
    }

    ui->progressBar->setValue(ui->progressBar->maximum());
}

void frmCodeCopy::copyFile(const QString &fileName, const QString &newName)
{
    //先删除文件再拷贝文件
    QFile::remove(newName);
    QFile::copy(fileName, newName);
    QString msg = QString("%1 -> %2").arg(TIMEMS).arg(newName);
    ui->txtResult->append(msg);
}

void frmCodeCopy::on_btnCopy_clicked()
{
    QString path = ui->txtPathInclude->text().trimmed();
    copyFile(path, true, false);
    QMessageBox::information(this, "提示", "恭喜发布文件完成!");
}

void frmCodeCopy::on_btnDo_clicked()
{
    //第一步:将designer下的头文件和源文件拷贝到临时目录 统一找文件很方便
    //designer下的文件永远保持最新
    QString pathDesigner = ui->txtPathDesigner->text().trimmed();
    QString pathTemp = pathDesigner + "/temp";
    copyFile(pathTemp, true, true);

    //第二步:遍历目标目录下的所有 .h .cpp 文件
    QString pathTarget = ui->cboxPathTarget->currentText().trimmed();
    getFileNames(pathTarget);
    qDebug() << fileNames;
    if (fileNames.count() <= 0) {
        return;
    }

    ui->progressBar->setRange(0, fileNames.count());
    ui->progressBar->setValue(0);

    //第三步:从designer目录挨个取出 h找include目录 cpp找src目录
    //第四步:找到则拷贝覆盖
    foreach (QString fileTarget, fileNames) {
        //打印信息执行进度条
        QString msg = QString("%1 -> %2").arg(TIMEMS).arg(fileTarget);
        ui->progressBar->setValue(ui->progressBar->value() + 1);

        //识别不同的文件夹
        if (fileTarget.endsWith(".h")) {
            ui->txtHeader->append(msg);
        } else if (fileTarget.endsWith(".cpp")) {
            ui->txtSource->append(msg);
        }

        QStringList list = fileTarget.split("/");
        QString fileTemp = QString("%1/%2").arg(pathTemp).arg(list.last());
        //从临时目录下对应的控件源码拷贝到目标路径下对应的控件目标路径的控件源码
        if (QFile(fileTemp).exists() && QFile(fileTarget).exists()) {
            copyFile(fileTemp, fileTarget);
        }
    }

    ui->progressBar->setValue(ui->progressBar->maximum());

    //第五步:删除临时目录
    deletePath(pathTemp);

    QMessageBox::information(this, "提示", "恭喜一键搞定咯!");
}
