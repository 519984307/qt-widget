#include "frmwave.h"
#include "ui_frmwave.h"

#include "../../demo/wave/wavebar/frmwavebar.h"
#include "../../demo/wave/wavedouble/frmwavedouble.h"
#include "../../demo/wave/waveline/frmwaveline.h"
#include "../../demo/wave/waveplot/frmwaveplot.h"
#include "../../demo/wave/wavechart/frmwavechart.h"
#include "../../demo/wave/wavedata/frmwavedata.h"
#include "../../demo/wave/wavewater/frmwavewater.h"

frmWave::frmWave(QWidget *parent) : QWidget(parent), ui(new Ui::frmWave)
{
    ui->setupUi(this);
    this->initForm();
}

frmWave::~frmWave()
{
    delete ui;
}

void frmWave::initForm()
{
    ui->stackedWidget->addWidget(new frmWaveBar);
    ui->stackedWidget->addWidget(new frmWaveDouble);
    ui->stackedWidget->addWidget(new frmWaveLine);
    ui->stackedWidget->addWidget(new frmWavePlot);
    ui->stackedWidget->addWidget(new frmWaveChart);
    ui->stackedWidget->addWidget(new frmWaveData);
    ui->stackedWidget->addWidget(new frmWaveWater);
}

void frmWave::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
