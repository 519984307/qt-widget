#include "flighttc.h"
#include "qmath.h"
#include "qdebug.h"

#ifndef noxmlsvg
#include "qgraphicssvgitem.h"
#endif

FlightTC::FlightTC(QWidget *parent) : QGraphicsView(parent)
{
    m_originalHeight = 240;
    m_originalWidth = 240;

    m_originalMarkCtr = QPointF(120.0f, 120.0f);
    m_originalBallCtr = QPointF(120.0f, -36.0f);

    m_backZ = -70;
    m_ballZ = -60;
    m_face1Z = -50;
    m_face2Z = -40;
    m_markZ = -30;
    m_caseZ = 10;

    reset();
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);
    m_scene->clear();
    init();

    this->setStyleSheet("background:transparent;border:0px");
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

FlightTC::~FlightTC()
{
    if (m_scene != 0) {
        m_scene->clear();
        delete m_scene;
        m_scene = 0;
    }

    reset();
}

void FlightTC::reinit()
{
    if (m_scene) {
        m_scene->clear();

        init();
    }
}

void FlightTC::update()
{
    updateView();
}

float FlightTC::getTurnRate() const
{
    return this->m_turnRate;
}

void FlightTC::setTurnRate(float turnRate)
{
    m_turnRate = turnRate;
    if (m_turnRate < -6.0f) {
        m_turnRate = -6.0f;
    }
    if (m_turnRate >  6.0f) {
        m_turnRate =  6.0f;
    }
    this->update();
}

float FlightTC::getSlipSkid() const
{
    return this->m_slipSkid;
}

void FlightTC::setSlipSkid(float slipSkid)
{
    m_slipSkid = slipSkid;
    if (m_slipSkid < -15.0f) {
        m_slipSkid = -15.0f;
    }
    if (m_slipSkid >  15.0f) {
        m_slipSkid =  15.0f;
    }
    this->update();
}

QSize FlightTC::sizeHint() const
{
    return QSize(300, 300);
}

QSize FlightTC::minimumSizeHint() const
{
    return QSize(30, 30);
}

void FlightTC::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    reinit();
}

void FlightTC::init()
{
#ifndef noxmlsvg
    m_scaleX = (float)width()  / (float)m_originalWidth;
    m_scaleY = (float)height() / (float)m_originalHeight;
    reset();

    m_itemBack = new QGraphicsSvgItem(":/svg/flight/tc_back.svg");
    m_itemBack->setCacheMode(QGraphicsItem::NoCache);
    m_itemBack->setZValue(m_backZ);
    m_itemBack->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_scene->addItem(m_itemBack);

    m_itemBall = new QGraphicsSvgItem(":/svg/flight/tc_ball.svg");
    m_itemBall->setCacheMode(QGraphicsItem::NoCache);
    m_itemBall->setZValue(m_ballZ);
    m_itemBall->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemBall->setTransformOriginPoint(m_originalBallCtr);
    m_scene->addItem(m_itemBall);

    m_itemFace_1 = new QGraphicsSvgItem(":/svg/flight/tc_face_1.svg");
    m_itemFace_1->setCacheMode(QGraphicsItem::NoCache);
    m_itemFace_1->setZValue(m_face1Z);
    m_itemFace_1->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_scene->addItem(m_itemFace_1);

    m_itemFace_2 = new QGraphicsSvgItem(":/svg/flight/tc_face_2.svg");
    m_itemFace_2->setCacheMode(QGraphicsItem::NoCache);
    m_itemFace_2->setZValue(m_face2Z);
    m_itemFace_2->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_scene->addItem(m_itemFace_2);

    m_itemMark = new QGraphicsSvgItem(":/svg/flight/tc_mark.svg");
    m_itemMark->setCacheMode(QGraphicsItem::NoCache);
    m_itemMark->setZValue(m_markZ);
    m_itemMark->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemMark->setTransformOriginPoint(m_originalMarkCtr);
    m_scene->addItem(m_itemMark);

    m_itemCase = new QGraphicsSvgItem(":/svg/flight/tc_case.svg");
    m_itemCase->setCacheMode(QGraphicsItem::NoCache);
    m_itemCase->setZValue(m_caseZ);
    m_itemCase->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_scene->addItem(m_itemCase);

    centerOn(width() / 2.0f, height() / 2.0f);
    updateView();
#endif
}

void FlightTC::reset()
{
    m_itemCase = 0;
    m_turnRate = 0.0f;
    m_slipSkid = 0.0f;
}

void FlightTC::updateView()
{
#ifndef noxmlsvg
    m_scaleX = (float)width()  / (float)m_originalWidth;
    m_scaleY = (float)height() / (float)m_originalHeight;
    m_itemBall->setRotation(-m_slipSkid);

    float angle = (m_turnRate / 3.0f) * 20.0f;
    m_itemMark->setRotation(angle);
    m_scene->update();
#endif
}
