#include "flighthsi.h"
#include "qmath.h"
#include "qdebug.h"

#ifndef noxmlsvg
#include "qgraphicssvgitem.h"
#endif

FlightHSI::FlightHSI(QWidget *parent) : QGraphicsView(parent)
{
    m_originalHeight = 240;
    m_originalWidth = 240;
    m_originalHsiCtr = QPointF(120.0f, 120.0f);

    m_faceZ = -20;
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

FlightHSI::~FlightHSI()
{
    if (m_scene != 0) {
        m_scene->clear();
        delete m_scene;
        m_scene = 0;
    }

    reset();
}

void FlightHSI::reinit()
{
    if (m_scene) {
        m_scene->clear();
        init();
    }
}

void FlightHSI::update()
{
    updateView();
}

float FlightHSI::getHeading() const
{
    return this->m_heading;
}

void FlightHSI::setHeading(float heading)
{
    m_heading = heading;
    this->update();
}

QSize FlightHSI::sizeHint() const
{
    return QSize(300, 300);
}

QSize FlightHSI::minimumSizeHint() const
{
    return QSize(30, 30);
}

void FlightHSI::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    reinit();
}

void FlightHSI::init()
{
#ifndef noxmlsvg
    m_scaleX = (float)width()  / (float)m_originalWidth;
    m_scaleY = (float)height() / (float)m_originalHeight;
    reset();

    m_itemFace = new QGraphicsSvgItem(":/svg/flight/hsi_face.svg");
    m_itemFace->setCacheMode(QGraphicsItem::NoCache);
    m_itemFace->setZValue(m_faceZ);
    m_itemFace->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemFace->setTransformOriginPoint(m_originalHsiCtr);
    m_scene->addItem(m_itemFace);

    m_itemCase = new QGraphicsSvgItem(":/svg/flight/hsi_case.svg");
    m_itemCase->setCacheMode(QGraphicsItem::NoCache);
    m_itemCase->setZValue(m_caseZ);
    m_itemCase->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_scene->addItem(m_itemCase);

    centerOn(width() / 2.0f, height() / 2.0f);
    updateView();
#endif
}

void FlightHSI::reset()
{
    m_itemFace = 0;
    m_itemCase = 0;

    m_heading = 0.0f;
}

void FlightHSI::updateView()
{
#ifndef noxmlsvg
    m_itemFace->setRotation(- m_heading);
    m_scene->update();
#endif
}
