#pragma execution_character_set("utf-8")

#include "frmcodesrc.h"
#include "ui_frmcodesrc.h"
#include "qfiledialog.h"
#include "qdatetime.h"
#include "qdir.h"
#include "qfile.h"
#include "qfileinfo.h"
#include "qmessagebox.h"
#include "qaction.h"
#include "qdebug.h"

#define TIMEMS QTime::currentTime().toString("hh:mm:ss zzz")

frmCodeSrc::frmCodeSrc(QWidget *parent) : QWidget(parent), ui(new Ui::frmCodeSrc)
{
    ui->setupUi(this);
    this->initForm();
    on_btnSelectModel1_clicked();
}

frmCodeSrc::~frmCodeSrc()
{
    delete ui;
}

void frmCodeSrc::initForm()
{
    ui->txtPathSrc->setText("G:/Qt开发/源码/qt-everywhere-src-5.15.2");

    QStringList names;
    names << "qt5compat" << "qtbase";
    names << "qtdeclarative" << "qtimageformats" << "qtmultimedia" << "qtserialbus" << "qtserialport";
    names << "qtsvg" << "qtscript" << "qtspeech" << "qtcharts" << "qtmqtt" << "qtpositioning";
    names << "qtsensors" << "qtlottie" << "qtscxml" << "qtxmlpatterns" << "qtvirtualkeyboard";
    names << "qtactiveqt" << "qtwinextras" << "qtx11extras" << "qtwayland";
    names << "qtconnectivity" << "qtcoap" << "qtremoteobjects" << "qtopcua";
    names << "qtwebchannel" << "qtwebglplugin" << "qtwebsockets" << "qtwebview" << "qtnetworkauth";
    names << "qtwebengine";
    names << "qt3d" << "qtquick3d" << "qtquickcontrols" << "qtquickcontrols2" << "qtquicktimeline";

    //加入复选框
    foreach (QString name, names) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(name);
        item->setCheckState(Qt::Unchecked);
        ui->listWidget->addItem(item);
    }
}

void frmCodeSrc::getFileNames(const QString &path)
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

void frmCodeSrc::on_btnSelect_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    if (!path.isEmpty()) {
        ui->txtPathSrc->setText(path);
    }
}

void frmCodeSrc::on_btnCopy_clicked()
{
    ui->txtResult->clear();
    ui->labCount->setText(QString("共 %1 个").arg(0));
    QString pathSrc = ui->txtPathSrc->text().trimmed();

    //查找选中目录的所有代码文件
    int count = ui->listWidget->count();
    for (int i = 0; i < count; ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            QString name = item->text();
            getFileNames(pathSrc + "/" + name + "/src");
        }
    }

    count = fileNames.count();
    if (count <= 0) {
        return;
    }

    ui->labCount->setText(QString("共 %1 个").arg(count));
    ui->progressBar->setRange(0, count);
    ui->progressBar->setValue(0);
    qApp->processEvents();

    //目录不存在则新建
    QString pathSrc2 = ui->txtPathSrc2->text().trimmed();
    QDir dir(pathSrc2);
    if (!dir.exists()) {
        dir.mkdir(pathSrc2);
    }

    //搞个计数
    count = 0;
    foreach (QString fileName, fileNames) {
        QString newName = fileName.split("/").last();
        newName = pathSrc2 + "/" + newName;
        QFile::copy(fileName, newName);
        count++;

        //到一定数量的则清空下
        if (count % 1000 == 0) {
            ui->txtResult->clear();
        }

        ui->txtResult->append(fileName);
        ui->progressBar->setValue(ui->progressBar->value() + 1);
        qApp->processEvents();
    }

    ui->progressBar->setValue(ui->progressBar->maximum());
    QMessageBox::information(this, "提示", "一键拷贝文件完成!");
}

void frmCodeSrc::on_btnSelectAll_clicked()
{
    int count = ui->listWidget->count();
    for (int i = 0; i < count; ++i) {
        ui->listWidget->item(i)->setCheckState(Qt::Checked);
    }
}

void frmCodeSrc::on_btnSelectNo_clicked()
{
    int count = ui->listWidget->count();
    for (int i = 0; i < count; ++i) {
        ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
    }
}

void frmCodeSrc::on_btnSelectModel1_clicked()
{
    QStringList names;
    names << "qt5compat" << "qtbase";

    int count = ui->listWidget->count();
    for (int i = 0; i < count; ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (names.contains(item->text())) {
            item->setCheckState(Qt::Checked);
        }
    }
}

void frmCodeSrc::on_btnSelectModel2_clicked()
{
    QStringList names;
    names << "qtdeclarative" << "qtimageformats" << "qtmultimedia" << "qtserialbus" << "qtserialport";
    names << "qtsvg" << "qtscript" << "qtspeech" << "qtcharts" << "qtmqtt" << "qtpositioning";

    int count = ui->listWidget->count();
    for (int i = 0; i < count; ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (names.contains(item->text())) {
            item->setCheckState(Qt::Checked);
        }
    }
}

void frmCodeSrc::on_txtPathSrc_textChanged(const QString &arg1)
{
    ui->txtPathSrc2->setText(arg1 + "2");
}

void frmCodeSrc::on_listWidget_itemPressed(QListWidgetItem *item)
{
    item->setCheckState(item->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked);
}
