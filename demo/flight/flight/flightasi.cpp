#include "flightasi.h"
#include "qmath.h"
#include "qdebug.h"

#ifndef noxmlsvg
#include "qgraphicssvgitem.h"
#endif

FlightASI::FlightASI(QWidget *parent) :  QGraphicsView(parent)
{
    m_originalHeight = 240;
    m_originalWidth = 240;
    m_originalAsiCtr = QPointF(120.0f, 120.0f);

    m_faceZ = -20;
    m_handZ = -10;
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

FlightASI::~FlightASI()
{
    if (m_scene != 0) {
        m_scene->clear();
        delete m_scene;
        m_scene = 0;
    }

    reset();
}

void FlightASI::reinit()
{
    if (m_scene) {
        m_scene->clear();

        init();
    }
}

void FlightASI::update()
{
    updateView();
}

float FlightASI::getAirspeed() const
{
    return this->m_airspeed;
}

void FlightASI::setAirspeed(float airspeed)
{
    m_airspeed = airspeed;
    if (m_airspeed <   0.0f) {
        m_airspeed =   0.0f;
    }
    if (m_airspeed > 235.0f) {
        m_airspeed = 235.0f;
    }
    this->update();
}

QSize FlightASI::sizeHint() const
{
    return QSize(300, 300);
}

QSize FlightASI::minimumSizeHint() const
{
    return QSize(30, 30);
}

void FlightASI::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    reinit();
}

void FlightASI::init()
{
#ifndef noxmlsvg
    m_scaleX = (float)width()  / (float)m_originalWidth;
    m_scaleY = (float)height() / (float)m_originalHeight;
    reset();

    m_itemFace = new QGraphicsSvgItem(":/svg/flight/asi_face.svg");
    m_itemFace->setCacheMode(QGraphicsItem::NoCache);
    m_itemFace->setZValue(m_faceZ);
    m_itemFace->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_scene->addItem(m_itemFace);

    m_itemHand = new QGraphicsSvgItem(":/svg/flight/asi_hand.svg");
    m_itemHand->setCacheMode(QGraphicsItem::NoCache);
    m_itemHand->setZValue(m_handZ);
    m_itemHand->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemHand->setTransformOriginPoint(m_originalAsiCtr);
    m_scene->addItem(m_itemHand);

    m_itemCase = new QGraphicsSvgItem(":/svg/flight/asi_case.svg");
    m_itemCase->setCacheMode(QGraphicsItem::NoCache);
    m_itemCase->setZValue(m_caseZ);
    m_itemCase->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_scene->addItem(m_itemCase);

    centerOn(width() / 2.0f, height() / 2.0f);
    updateView();
#endif
}

void FlightASI::reset()
{
    m_itemFace = 0;
    m_itemHand = 0;
    m_itemCase = 0;

    m_airspeed = 0.0f;
}

void FlightASI::updateView()
{
#ifndef noxmlsvg
    float angle = 0.0f;
    if (m_airspeed < 40.0f) {
        angle = 0.9f * m_airspeed;
    } else if (m_airspeed < 70.0f) {
        angle = 36.0f + 1.8f * (m_airspeed - 40.0f);
    } else if (m_airspeed < 130.0f) {
        angle = 90.0f + 2.0f * (m_airspeed - 70.0f);
    } else if (m_airspeed < 160.0f) {
        angle = 210.0f + 1.8f * (m_airspeed - 130.0f);
    } else {
        angle = 264.0f + 1.2f * (m_airspeed - 160.0f);
    }

    m_itemHand->setRotation(angle);
    m_scene->update();
#endif
}
