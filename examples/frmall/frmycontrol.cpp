#include "frmycontrol.h"
#include "ui_frmycontrol.h"

#include "../../demo/ycontrol/ycontrol/ycontrol.h"
#include "../../demo/ycontrol/frmycombobox.h"
#include "../../demo/ycontrol/frmyspinbox.h"
#include "../../demo/ycontrol/frmyscrollbar.h"
#include "../../demo/ycontrol/frmytabwidget.h"
#include "../../demo/ycontrol/frmylistwidget.h"
#include "../../demo/ycontrol/frmytreewidget.h"
#include "../../demo/ycontrol/frmytablewidget.h"
#include "../../demo/ycontrol/frmycontrolall.h"

frmYControl::frmYControl(QWidget *parent) : QWidget(parent), ui(new Ui::frmYControl)
{
    ui->setupUi(this);
    this->initForm();
    YControl::initStyle(ui->stackedWidget);
}

frmYControl::~frmYControl()
{
    delete ui;
}

void frmYControl::initForm()
{
    ui->stackedWidget->addWidget(new frmYComboBox);
    ui->stackedWidget->addWidget(new frmYSpinBox);
    ui->stackedWidget->addWidget(new frmYScrollBar);
    ui->stackedWidget->addWidget(new frmYTabWidget);
    ui->stackedWidget->addWidget(new frmYListWidget);
    ui->stackedWidget->addWidget(new frmYTreeWidget);
    ui->stackedWidget->addWidget(new frmYTableWidget);
    ui->stackedWidget->addWidget(new frmYControlAll);
}

void frmYControl::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
