#pragma execution_character_set("utf-8")

#include "frmcodeclean.h"
#include "ui_frmcodeclean.h"
#include "qfiledialog.h"
#include "qfile.h"
#include "qdebug.h"

frmCodeClean::frmCodeClean(QWidget *parent) : QWidget(parent), ui(new Ui::frmCodeClean)
{
    ui->setupUi(this);
}

frmCodeClean::~frmCodeClean()
{
    delete ui;
}

void frmCodeClean::on_btnSelect_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择代码文件");
    if (!fileName.isEmpty()) {
        ui->txtFile->setText(fileName);
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QString text = file.readAll();
            ui->txtCode->setText(text);
        }
    }
}

void frmCodeClean::on_btnDo_clicked()
{
    ui->txtResult->clear();
    QString text = ui->txtCode->toPlainText();
    QStringList list = text.split("\n");
    foreach (QString line, list) {
        //过滤空行
        QString temp = line.trimmed();
        if (temp.isEmpty()) {
            continue;
        }

        //过滤注释
        if (line.contains("//") || line.startsWith("/*") || line.startsWith(" * ") || line.startsWith(" */")) {
            continue;
        }

        ui->txtResult->append(line);
    }
}
