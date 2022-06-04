#include "frmcolor.h"
#include "ui_frmcolor.h"

#include "../../demo/color/colorpanel/frmcolorpanel.h"
#include "../../demo/color/colorpanelbtn/frmcolorpanelbtn.h"
#include "../../demo/color/colorpanelfader/frmcolorpanelfader.h"
#include "../../demo/color/colorpanelhsb/frmcolorpanelhsb.h"
#include "../../demo/color/colorbutton/frmcolorbutton.h"
#include "../../demo/color/colorcombobox/frmcolorcombobox.h"
#include "../../demo/color/colorstyle/frmcolorstyle.h"

frmColor::frmColor(QWidget *parent) : QWidget(parent), ui(new Ui::frmColor)
{
    ui->setupUi(this);
    this->initForm();
}

frmColor::~frmColor()
{
    delete ui;
}

void frmColor::initForm()
{
    ui->stackedWidget->addWidget(new frmColorPanel);
    ui->stackedWidget->addWidget(new frmColorPanelBtn);
    ui->stackedWidget->addWidget(new frmColorPanelFader);
    ui->stackedWidget->addWidget(new frmColorPanelHSB);
    ui->stackedWidget->addWidget(new frmColorButton);
    ui->stackedWidget->addWidget(new frmColorComboBox);
    ui->stackedWidget->addWidget(new frmColorStyle);
}

void frmColor::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
