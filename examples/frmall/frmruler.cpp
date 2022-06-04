#include "frmruler.h"
#include "ui_frmruler.h"

#include "../../demo/ruler/rulerbar/frmrulerbar.h"
#include "../../demo/ruler/rulerline/frmrulerline.h"
#include "../../demo/ruler/rulerslider/frmrulerslider.h"
#include "../../demo/ruler/rulerdouble/frmrulerdouble.h"
#include "../../demo/ruler/rulertemp/frmrulertemp.h"
#include "../../demo/ruler/rulerscale/frmrulerscale.h"
#include "../../demo/ruler/rulerprogress/frmrulerprogress.h"

frmRuler::frmRuler(QWidget *parent) : QWidget(parent), ui(new Ui::frmRuler)
{
    ui->setupUi(this);
    this->initForm();
}

frmRuler::~frmRuler()
{
    delete ui;
}

void frmRuler::initForm()
{
    ui->stackedWidget->addWidget(new frmRulerBar);
    ui->stackedWidget->addWidget(new frmRulerLine);
    ui->stackedWidget->addWidget(new frmRulerSlider);
    ui->stackedWidget->addWidget(new frmRulerDouble);
    ui->stackedWidget->addWidget(new frmRulerTemp);
    ui->stackedWidget->addWidget(new frmRulerScale);
    ui->stackedWidget->addWidget(new frmRulerProgress);
}

void frmRuler::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
