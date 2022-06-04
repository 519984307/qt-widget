#pragma execution_character_set("utf-8")

#include "frmiconeditor.h"
#include "ui_frmiconeditor.h"
#include "qfiledialog.h"

frmIconEditor::frmIconEditor(QWidget *parent) : QWidget(parent), ui(new Ui::frmIconEditor)
{
    ui->setupUi(this);
    this->initForm();
}

frmIconEditor::~frmIconEditor()
{
    delete ui;
}

void frmIconEditor::initForm()
{
    for (int i = 3; i < 50; i++) {
        ui->cboxZoom->addItem(QString::number(i));
    }

    int value = 25;
    ui->cboxZoom->setCurrentIndex(ui->cboxZoom->findText(QString::number(value)));
    ui->iconEditor->setZoomFactor(value);
}

void frmIconEditor::on_btnOpen_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "打开");
    if (!file.isEmpty()) {
        ui->iconEditor->setIconImage(file);
    }
}

void frmIconEditor::on_btnSave_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, "保存");
    if (!file.isEmpty()) {
        ui->iconEditor->saveIcon(file);
    }
}

void frmIconEditor::on_btnSaveBg_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, "保存");
    if (!file.isEmpty()) {
        ui->iconEditor->saveBg(file);
    }
}

void frmIconEditor::on_cboxZoom_activated(int)
{
    ui->iconEditor->setZoomFactor(ui->cboxZoom->currentText().toInt());
}
