#include "frmcustomgraphics.h"
#include "ui_frmcustomgraphics.h"
#include "qdebug.h"

frmCustomGraphics::frmCustomGraphics(QWidget *parent) : QWidget(parent), ui(new Ui::frmCustomGraphics)
{
    ui->setupUi(this);
    //点坐标集合以信号的形式传过来
    connect(ui->customGraphics, SIGNAL(receivePoints(QVector<QPoint>)),
            this, SLOT(receivePoints(QVector<QPoint>)));
}

frmCustomGraphics::~frmCustomGraphics()
{
    delete ui;
}

void frmCustomGraphics::receivePoints(const QVector<QPoint> &points)
{
    qDebug() << points;
}

void frmCustomGraphics::on_btnOk_clicked()
{
    ui->customGraphics->getPoints();
}
