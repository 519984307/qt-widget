#include "frmwidget.h"
#include "ui_frmwidget.h"

#include "../../demo/widget/movewidget/frmmovewidget.h"
#include "../../demo/widget/framelesswidget/frmframelesswidget.h"
#include "../../demo/widget/gifwidget/frmgifwidget.h"
#include "../../demo/widget/screenwidget/frmscreenwidget.h"
#include "../../demo/widget/colorwidget/frmcolorwidget.h"
#include "../../demo/widget/maskwidget/frmmaskwidget.h"
#include "../../demo/widget/bottomwidget/frmbottomwidget.h"

frmWidget::frmWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmWidget)
{
    ui->setupUi(this);
    this->initForm();
}

frmWidget::~frmWidget()
{
    delete ui;
}

void frmWidget::initForm()
{
    ui->stackedWidget->addWidget(new frmMoveWidget);
    ui->stackedWidget->addWidget(new frmFramelessWidget);
    ui->stackedWidget->addWidget(new frmGifWidget);
    ui->stackedWidget->addWidget(new frmScreenWidget);
    ui->stackedWidget->addWidget(new frmColorWidget);
    ui->stackedWidget->addWidget(new frmMaskWidget);
    ui->stackedWidget->addWidget(new frmBottomWidget);
}

void frmWidget::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
