#include "frmprogress.h"
#include "ui_frmprogress.h"

#include "../../demo/progress/progresswater/frmprogresswater.h"
#include "../../demo/progress/progresscolor/frmprogresscolor.h"
#include "../../demo/progress/progresspercent/frmprogresspercent.h"
#include "../../demo/progress/progressround/frmprogressround.h"
#include "../../demo/progress/progresswait/frmprogresswait.h"
#include "../../demo/progress/progressbutton/frmprogressbutton.h"
#include "../../demo/progress/progressthree/frmprogressthree.h"
#include "../../demo/progress/progressplay/frmprogressplay.h"
#include "../../demo/progress/progressring/frmprogressring.h"
#include "../../demo/progress/progressarc/frmprogressarc.h"
#include "../../demo/progress/progressshadow/frmprogressshadow.h"
#include "../../demo/progress/progresstip/frmprogresstip.h"
#include "../../demo/progress/progresscountdown/frmprogresscountdown.h"

frmProgress::frmProgress(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgress)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgress::~frmProgress()
{
    delete ui;
}

void frmProgress::initForm()
{
    ui->stackedWidget->addWidget(new frmProgressWater);
    ui->stackedWidget->addWidget(new frmProgressPercent);
    ui->stackedWidget->addWidget(new frmProgressRound);
    ui->stackedWidget->addWidget(new frmProgressWait);
#ifdef Q_OS_ANDROID
    ui->stackedWidget->addWidget(new frmProgressWait);
#else
    ui->stackedWidget->addWidget(new frmProgressColor);
#endif
    ui->stackedWidget->addWidget(new frmProgressButton);
    ui->stackedWidget->addWidget(new frmProgressThree);
    ui->stackedWidget->addWidget(new frmProgressPlay);
    ui->stackedWidget->addWidget(new frmProgressRing);
    ui->stackedWidget->addWidget(new frmProgressArc);
    ui->stackedWidget->addWidget(new frmProgressShadow);
    ui->stackedWidget->addWidget(new frmProgressTip);
    ui->stackedWidget->addWidget(new frmProgressCountDown);
}

void frmProgress::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
