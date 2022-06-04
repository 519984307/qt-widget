#include "frmscantantan.h"
#include "ui_frmscantantan.h"

frmScanTanTan::frmScanTanTan(QWidget *parent) : QWidget(parent), ui(new Ui::frmScanTanTan)
{
    ui->setupUi(this);
}

frmScanTanTan::~frmScanTanTan()
{
    delete ui;
}

void frmScanTanTan::initForm()
{
    ui->scanTanTan->setImage(QPixmap(":/image/liuyifei3.jpg"));
}
