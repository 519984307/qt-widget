#include "frmflightall.h"
#include "ui_frmflightall.h"
#include "squarelayout.h"
#include "qtimer.h"

frmFlightAll::frmFlightAll(QWidget *parent) : QWidget(parent), ui(new Ui::frmFlightAll)
{
    ui->setupUi(this);
    this->initForm();
}

frmFlightAll::~frmFlightAll()
{
    delete ui;
}

void frmFlightAll::showEvent(QShowEvent *)
{
    timer->start();
}

void frmFlightAll::hideEvent(QHideEvent *)
{
    timer->stop();
}

void frmFlightAll::initForm()
{
    //将控件添加到正方形布局中
    SquareLayout *squareLayout1 = new SquareLayout;
    squareLayout1->addWidget(ui->flightADI);
    QWidget *widget1 = new QWidget;
    widget1->setLayout(squareLayout1);

    SquareLayout *squareLayout2 = new SquareLayout;
    squareLayout2->addWidget(ui->flightALT);
    QWidget *widget2 = new QWidget;
    widget2->setLayout(squareLayout2);

    SquareLayout *squareLayout3 = new SquareLayout;
    squareLayout3->addWidget(ui->flightASI);
    QWidget *widget3 = new QWidget;
    widget3->setLayout(squareLayout3);

    SquareLayout *squareLayout4 = new SquareLayout;
    squareLayout4->addWidget(ui->flightHSI);
    QWidget *widget4 = new QWidget;
    widget4->setLayout(squareLayout4);

    SquareLayout *squareLayout5 = new SquareLayout;
    squareLayout5->addWidget(ui->flightTC);
    QWidget *widget5 = new QWidget;
    widget5->setLayout(squareLayout5);

    SquareLayout *squareLayout6 = new SquareLayout;
    squareLayout6->addWidget(ui->flightVSI);
    QWidget *widget6 = new QWidget;
    widget6->setLayout(squareLayout6);

    //新建垂直布局将正方形布局和其他控件加进来
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(widget1, 0, 0);
    layout->addWidget(widget2, 0, 1);
    layout->addWidget(widget3, 0, 2);
    layout->addWidget(widget4, 1, 0);
    layout->addWidget(widget5, 1, 1);
    layout->addWidget(widget6, 1, 2);
    this->setLayout(layout);

    //定时器模拟数据
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(testData()));
    timer->setInterval(50);    
}

void frmFlightAll::testData()
{
    static int roll = -180;
    static bool roolAdd = true;
    addValue(roll, roolAdd, -180, 180);
    ui->flightADI->setRoll(roll);

    static int pitch = -25;
    static bool pitchAdd = true;
    addValue(pitch, pitchAdd, -25, 25);
    //ui->flightADI->setPitch(pitch);

    static int altitude = 0;
    static bool altitudeAdd = true;
    addValue(altitude, altitudeAdd, 0, 10000, 10);
    ui->flightALT->setAltitude(altitude);

    static int pressure = 280;
    static bool pressureAdd = true;
    addValue(pressure, pressureAdd, 280, 315);
    ui->flightALT->setPressure((float)altitude / 10);

    static int airspeed = 0;
    static bool airspeedAdd = true;
    addValue(airspeed, airspeedAdd, 0, 235);
    ui->flightASI->setAirspeed(airspeed);

    static int heading = 0;
    static bool headingAdd = true;
    addValue(heading, headingAdd, 0, 360);
    ui->flightHSI->setHeading(heading);

    static int turnRate = -6;
    static bool turnRateAdd = true;
    addValue(turnRate, turnRateAdd, -6, 6);
    ui->flightTC->setTurnRate(turnRate);

    static int slipSkid = -15;
    static bool slipSkidAdd = true;
    addValue(slipSkid, slipSkidAdd, -15, 15);
    ui->flightTC->setSlipSkid(slipSkid);

    static int climbRate = -2000;
    static bool climbRateAdd = true;
    addValue(climbRate, climbRateAdd, -2000, 2000, 20);
    ui->flightVSI->setClimbRate(climbRate);
}

void frmFlightAll::addValue(int &value, bool &add, int min, int max, int step)
{
    //到了最小值则增加到了最大值则减少
    add ? value += step : value -= step;
    if (value == max) {
        add = false;
    } else if (value == min) {
        add = true;
    }
}
