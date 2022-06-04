#include "frmtasktableview.h"
#include "ui_frmtasktableview.h"
#include "qcolordialog.h"
#include "qdebug.h"

frmTaskTableView::frmTaskTableView(QWidget *parent) : QWidget(parent), ui(new Ui::frmTaskTableView)
{
    ui->setupUi(this);
    this->initForm();
}

frmTaskTableView::~frmTaskTableView()
{

}

void frmTaskTableView::initForm()
{
    ui->taskTableView2->setBgColor(QColor(100, 100, 100));
    ui->taskTableView2->setGridColor(QColor(35, 35, 35));
    ui->taskTableView2->setHeaderBgColor(QColor(50, 50, 50));
    ui->taskTableView2->setHeaderTextColor(QColor(250, 250, 250));
    ui->taskTableView2->setNormalColor(QColor(45, 45, 45));
    ui->taskTableView2->setSelectColor(QColor(162, 121, 197));

    QList<QPushButton *> btns = this->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(clicked()));
    }
}

void frmTaskTableView::clicked()
{
    QPushButton *btn = (QPushButton *)sender();
    QColor color = QColorDialog::getColor();
    if (!color.isValid()) {
        return;
    }

    if (btn == ui->btnBgColor) {
        ui->taskTableView1->setBgColor(color);
    } else if (btn == ui->btnGridColor) {
        ui->taskTableView1->setGridColor(color);
    } else if (btn == ui->btnHeaderBgColor) {
        ui->taskTableView1->setHeaderBgColor(color);
    } else if (btn == ui->btnHeaderTextColor) {
        ui->taskTableView1->setHeaderTextColor(color);
    } else if (btn == ui->btnNormalColor) {
        ui->taskTableView1->setNormalColor(color);
    } else if (btn == ui->btnSelectColor) {
        ui->taskTableView1->setSelectColor(color);
    }
}
