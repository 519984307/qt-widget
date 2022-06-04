#include "frmflight.h"
#include "ui_frmflight.h"

#include "../../demo/flight/frmflightadi.h"
#include "../../demo/flight/frmflightalt.h"
#include "../../demo/flight/frmflightasi.h"
#include "../../demo/flight/frmflighthsi.h"
#include "../../demo/flight/frmflightnav.h"
#include "../../demo/flight/frmflightpfd.h"
#include "../../demo/flight/frmflighttc.h"
#include "../../demo/flight/frmflightvsi.h"
#include "../../demo/flight/frmflightall.h"

frmFlight::frmFlight(QWidget *parent) : QWidget(parent), ui(new Ui::frmFlight)
{
    ui->setupUi(this);
    this->initForm();
}

frmFlight::~frmFlight()
{
    delete ui;
}

void frmFlight::initForm()
{
    ui->stackedWidget->addWidget(new frmFlightADI);
    ui->stackedWidget->addWidget(new frmFlightALT);
    ui->stackedWidget->addWidget(new frmFlightASI);
    ui->stackedWidget->addWidget(new frmFlightHSI);
    ui->stackedWidget->addWidget(new frmFlightNAV);
    ui->stackedWidget->addWidget(new frmFlightPFD);
    ui->stackedWidget->addWidget(new frmFlightTC);
    ui->stackedWidget->addWidget(new frmFlightVSI);
    ui->stackedWidget->addWidget(new frmFlightAll);
}

void frmFlight::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
