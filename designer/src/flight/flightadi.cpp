#include "flightadi.h"
#include "qmath.h"
#include "qdebug.h"

#ifndef noxmlsvg
#include "qgraphicssvgitem.h"
#endif

FlightADI::FlightADI(QWidget *parent) : QGraphicsView(parent)
{
    m_originalHeight = 240;
    m_originalWidth = 240;
    m_originalPixPerDeg = 1.7f;
    m_originalAdiCtr = QPointF(120.0f, 120.0f);

    m_backZ = -30;
    m_faceZ = -20;
    m_ringZ = -10;
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

FlightADI::~FlightADI()
{
    if (m_scene != 0) {
        m_scene->clear();
        delete m_scene;
        m_scene = 0;
    }

    reset();
}

void FlightADI::reinit()
{
    if (m_scene) {
        m_scene->clear();
        init();
    }
}

void FlightADI::update()
{
    updateView();
    m_faceDeltaX_old  = m_faceDeltaX_new;
    m_faceDeltaY_old  = m_faceDeltaY_new;
}

float FlightADI::getRoll() const
{
    return this->m_roll;
}

void FlightADI::setRoll(float roll)
{
    m_roll = roll;
    if (m_roll < -180.0f) {
        m_roll = -180.0f;
    }
    if (m_roll >  180.0f) {
        m_roll =  180.0f;
    }
    this->update();
}

float FlightADI::getPitch() const
{
    return this->m_pitch;
}

void FlightADI::setPitch(float pitch)
{
    m_pitch = pitch;
    if (m_pitch < -25.0f) {
        m_pitch = -25.0f;
    }
    if (m_pitch >  25.0f) {
        m_pitch =  25.0f;
    }
    this->update();
}

QSize FlightADI::sizeHint() const
{
    return QSize(300, 300);
}

QSize FlightADI::minimumSizeHint() const
{
    return QSize(30, 30);
}

void FlightADI::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    reinit();
}

void FlightADI::init()
{
#ifndef noxmlsvg
    m_scaleX = (float)width()  / (float)m_originalWidth;
    m_scaleY = (float)height() / (float)m_originalHeight;
    reset();

    m_itemBack = new QGraphicsSvgItem(":/svg/flight/adi_back.svg");
    m_itemBack->setCacheMode(QGraphicsItem::NoCache);
    m_itemBack->setZValue(m_backZ);
    m_itemBack->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemBack->setTransformOriginPoint(m_originalAdiCtr);
    m_scene->addItem(m_itemBack);

    m_itemFace = new QGraphicsSvgItem(":/svg/flight/adi_face.svg");
    m_itemFace->setCacheMode(QGraphicsItem::NoCache);
    m_itemFace->setZValue(m_faceZ);
    m_itemFace->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemFace->setTransformOriginPoint(m_originalAdiCtr);
    m_scene->addItem(m_itemFace);

    m_itemRing = new QGraphicsSvgItem(":/svg/flight/adi_ring.svg");
    m_itemRing->setCacheMode(QGraphicsItem::NoCache);
    m_itemRing->setZValue(m_ringZ);
    m_itemRing->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemRing->setTransformOriginPoint(m_originalAdiCtr);
    m_scene->addItem(m_itemRing);

    m_itemCase = new QGraphicsSvgItem(":/svg/flight/adi_case.svg");
    m_itemCase->setCacheMode(QGraphicsItem::NoCache);
    m_itemCase->setZValue(m_caseZ);
    m_itemCase->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_scene->addItem(m_itemCase);

    centerOn(width() / 2.0f, height() / 2.0f);
    updateView();
#endif
}

void FlightADI::reset()
{
    m_itemBack = 0;
    m_itemFace = 0;
    m_itemRing = 0;
    m_itemCase = 0;

    m_roll = 0.0f;
    m_pitch = 0.0f;

    m_faceDeltaX_new = 0.0f;
    m_faceDeltaX_old = 0.0f;
    m_faceDeltaY_new = 0.0f;
    m_faceDeltaY_old = 0.0f;
}

void FlightADI::updateView()
{
#ifndef noxmlsvg
    m_scaleX = (float)width()  / (float)m_originalWidth;
    m_scaleY = (float)height() / (float)m_originalHeight;

    m_itemBack->setRotation(-m_roll);
    m_itemFace->setRotation(-m_roll);
    m_itemRing->setRotation(-m_roll);

    float roll_rad = M_PI * m_roll / 180.0;
    float delta = m_originalPixPerDeg * m_pitch;

    m_faceDeltaX_new = m_scaleX * delta * sin(roll_rad);
    m_faceDeltaY_new = m_scaleY * delta * cos(roll_rad);

    m_itemFace->moveBy(m_faceDeltaX_new - m_faceDeltaX_old, m_faceDeltaY_new - m_faceDeltaY_old);
    m_scene->update();
#endif
}
