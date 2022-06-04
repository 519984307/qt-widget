#include "frmtool.h"
#include "ui_frmtool.h"

#include "../../demo/tool/iptool/frmiptool.h"
#include "../../demo/tool/pngtool/frmpngtool.h"
#include "../../demo/tool/textwrite/frmtextwrite.h"
#include "../../demo/tool/codecount/frmcodecount.h"
#include "../../demo/tool/codetool/frmcodetool.h"
#include "../../demo/tool/codecopy/frmcodecopy.h"
#include "../../demo/tool/codesrc/frmcodesrc.h"
#include "../../demo/tool/codeclean/frmcodeclean.h"

frmTool::frmTool(QWidget *parent) : QWidget(parent), ui(new Ui::frmTool)
{
    ui->setupUi(this);
    this->initForm();
}

frmTool::~frmTool()
{
    delete ui;
}

void frmTool::initForm()
{
    ui->stackedWidget->addWidget(new frmIPTool);
    ui->stackedWidget->addWidget(new frmPngTool);
    ui->stackedWidget->addWidget(new frmTextWrite);
    ui->stackedWidget->addWidget(new frmCodeCount);
    ui->stackedWidget->addWidget(new frmCodeTool);
    ui->stackedWidget->addWidget(new frmCodeCopy);
    ui->stackedWidget->addWidget(new frmCodeSrc);
    ui->stackedWidget->addWidget(new frmCodeClean);
}

void frmTool::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
