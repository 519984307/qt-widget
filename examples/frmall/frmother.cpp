#include "frmother.h"
#include "ui_frmother.h"

#include "../../demo/other/panelmovewidget/frmpanelmovewidget.h"
#include "../../demo/other/panelitem/frmpanelitem.h"
#include "../../demo/other/panelwidget/frmpanelwidget.h"
#include "../../demo/other/lcddatetime/frmlcddatetime.h"
#include "../../demo/other/lcdnumber/frmlcdnumber.h"
#include "../../demo/other/lednumber/frmlednumber.h"
#include "../../demo/other/ledtext/frmledtext.h"
#include "../../demo/other/devicesizetable/frmdevicesizetable.h"
#include "../../demo/other/cpumemorylabel/frmcpumemorylabel.h"
#include "../../demo/other/textmovewidget/frmtextmovewidget.h"
#include "../../demo/other/verifiedcode/frmverifiedcode.h"
#include "../../demo/other/iconeditor/frmiconeditor.h"
#include "../../demo/other/ipaddress/frmipaddress.h"
#include "../../demo/other/antline/frmantline.h"
#include "../../demo/other/selectwidget/frmselectwidget.h"
#include "../../demo/other/flowlayout/frmflowlayout.h"
#include "../../demo/other/squarelayout/frmsquarelayout.h"

frmOther::frmOther(QWidget *parent) : QWidget(parent), ui(new Ui::frmOther)
{
    ui->setupUi(this);
    this->initForm();
}

frmOther::~frmOther()
{
    delete ui;
}

void frmOther::initForm()
{
    ui->stackedWidget->addWidget(new frmPanelMoveWidget);
    ui->stackedWidget->addWidget(new frmPanelItem);
    ui->stackedWidget->addWidget(new frmPanelWidget);
    ui->stackedWidget->addWidget(new frmLcdDateTime);
    ui->stackedWidget->addWidget(new frmLcdNumber);
    ui->stackedWidget->addWidget(new frmLedNumber);
    ui->stackedWidget->addWidget(new frmLedText);
    ui->stackedWidget->addWidget(new frmDeviceSizeTable);
    ui->stackedWidget->addWidget(new frmCpuMemoryLabel);
    ui->stackedWidget->addWidget(new frmTextMoveWidget);
    ui->stackedWidget->addWidget(new frmVerifiedCode);
    ui->stackedWidget->addWidget(new frmIconEditor);
    ui->stackedWidget->addWidget(new frmIPAddress);
    ui->stackedWidget->addWidget(new frmAntLine);
    ui->stackedWidget->addWidget(new frmSelectWidget);
    ui->stackedWidget->addWidget(new frmFlowLayout);
    ui->stackedWidget->addWidget(new frmSquareLayout);
}

void frmOther::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
