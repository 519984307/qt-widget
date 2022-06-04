#include "flightvsi.h"
#include "qmath.h"
#include "qdebug.h"

#ifndef noxmlsvg
#include "qgraphicssvgitem.h"
#endif

FlightVSI::FlightVSI(QWidget *parent) :  QGraphicsView(parent)
{
    m_originalHeight = 240;
    m_originalWidth = 240;
    m_originalVsiCtr = QPointF(120.0f, 120.0f);

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

FlightVSI::~FlightVSI()
{
    if (m_scene != 0) {
        m_scene->clear();
        delete m_scene;
        m_scene = 0;
    }

    reset();
}

void FlightVSI::reinit()
{
    if (m_scene) {
        m_scene->clear();

        init();
    }
}

void FlightVSI::update()
{
    updateView();
}

float FlightVSI::getClimbRate() const
{
    return m_climbRate;
}

void FlightVSI::setClimbRate(float climbRate)
{
    m_climbRate = climbRate;
    if (m_climbRate < -2000.0f) {
        m_climbRate = -2000.0f;
    }
    if (m_climbRate >  2000.0f) {
        m_climbRate =  2000.0f;
    }
    this->update();
}

QSize FlightVSI::sizeHint() const
{
    return QSize(300, 300);
}

QSize FlightVSI::minimumSizeHint() const
{
    return QSize(30, 30);
}

void FlightVSI::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    reinit();
}

void FlightVSI::init()
{
#ifndef noxmlsvg
    m_scaleX = (float)width()  / (float)m_originalWidth;
    m_scaleY = (float)height() / (float)m_originalHeight;
    reset();

    m_itemFace = new QGraphicsSvgItem(":/svg/flight/vsi_face.svg");
    m_itemFace->setCacheMode(QGraphicsItem::NoCache);
    m_itemFace->setZValue(m_faceZ);
    m_itemFace->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_scene->addItem(m_itemFace);

    m_itemHand = new QGraphicsSvgItem(":/svg/flight/vsi_hand.svg");
    m_itemHand->setCacheMode(QGraphicsItem::NoCache);
    m_itemHand->setZValue(m_handZ);
    m_itemHand->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemHand->setTransformOriginPoint(m_originalVsiCtr);
    m_scene->addItem(m_itemHand);

    m_itemCase = new QGraphicsSvgItem(":/svg/flight/vsi_case.svg");
    m_itemCase->setCacheMode(QGraphicsItem::NoCache);
    m_itemCase->setZValue(m_caseZ);
    m_itemCase->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_scene->addItem(m_itemCase);

    centerOn(width() / 2.0f, height() / 2.0f);
    updateView();
#endif
}

void FlightVSI::reset()
{
    m_itemFace = 0;
    m_itemHand = 0;
    m_itemCase = 0;

    m_climbRate = 0.0f;
}

void FlightVSI::updateView()
{
#ifndef noxmlsvg
    m_itemHand->setRotation(m_climbRate * 0.086f);
    m_scene->update();
#endif
}
