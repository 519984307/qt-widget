#include "frmnav.h"
#include "ui_frmnav.h"

#include "../../demo/nav/navbutton/frmnavbutton.h"
#include "../../demo/nav/navlabel/frmnavlabel.h"
#include "../../demo/nav/navprogress/frmnavprogress.h"
#include "../../demo/nav/navlistview/frmnavlistview.h"
#include "../../demo/nav/navlistview/frmnavlistviewform.h"
#include "../../demo/nav/navbar/frmnavbar.h"
#include "../../demo/nav/navbar/frmnavbarform.h"
#include "../../demo/nav/navbuttongroup/frmnavbuttongroup.h"
#include "../../demo/nav/navtitle/frmnavtitle.h"
#include "../../demo/nav/navpage/frmnavpage.h"

frmNav::frmNav(QWidget *parent) : QWidget(parent), ui(new Ui::frmNav)
{
    ui->setupUi(this);
    this->initForm();
}

frmNav::~frmNav()
{
    delete ui;
}

void frmNav::initForm()
{
    ui->stackedWidget->addWidget(new frmNavButton);
    ui->stackedWidget->addWidget(new frmNavLabel);
    ui->stackedWidget->addWidget(new frmNavProgress);
    ui->stackedWidget->addWidget(new frmNavListView);
    ui->stackedWidget->addWidget(new frmNavListViewForm);
    ui->stackedWidget->addWidget(new frmNavBar);
    ui->stackedWidget->addWidget(new frmNavBarForm);
    ui->stackedWidget->addWidget(new frmNavButtonGroup);
    ui->stackedWidget->addWidget(new frmNavTitle);
    ui->stackedWidget->addWidget(new frmNavPage);
}

void frmNav::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
