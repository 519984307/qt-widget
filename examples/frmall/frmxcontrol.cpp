#include "frmxcontrol.h"
#include "ui_frmxcontrol.h"

#include "../../demo/xcontrol/xlistwidget/frmxlistwidget.h"
#include "../../demo/xcontrol/xlistwidgetvs/frmxlistwidgetvs.h"
#include "../../demo/xcontrol/xlistwidgetvt/frmxlistwidgetvt.h"
#include "../../demo/xcontrol/xslider/frmxslider.h"
#include "../../demo/xcontrol/xprogressbar/frmxprogressbar.h"
#include "../../demo/xcontrol/xcombobox/frmxcombobox.h"
#include "../../demo/xcontrol/xstackwidget/frmxstackwidget.h"
#include "../../demo/xcontrol/xtablewidget/frmxtablewidget.h"

frmXControl::frmXControl(QWidget *parent) : QWidget(parent), ui(new Ui::frmXControl)
{
    ui->setupUi(this);
    this->initForm();
}

frmXControl::~frmXControl()
{
    delete ui;
}

void frmXControl::initForm()
{
    ui->stackedWidget->addWidget(new frmXListWidget);
    ui->stackedWidget->addWidget(new frmXListWidgetVS);
    ui->stackedWidget->addWidget(new frmXListWidgetVT);
    ui->stackedWidget->addWidget(new frmXSlider);
    ui->stackedWidget->addWidget(new frmXProgressBar);
    ui->stackedWidget->addWidget(new frmXComboBox);
    ui->stackedWidget->addWidget(new frmXStackWidget);
    ui->stackedWidget->addWidget(new frmXTableWidget);
}

void frmXControl::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
