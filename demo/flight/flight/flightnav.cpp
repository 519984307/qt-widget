#include "flightnav.h"
#include "qmath.h"
#include "qdebug.h"

#ifndef noxmlsvg
#include "qgraphicssvgitem.h"
#endif

FlightNAV::FlightNAV(QWidget *parent) : QGraphicsView(parent)
{
    m_crsTextColor = QColor(0, 255, 0);
    m_hdgTextColor = QColor(255, 0, 255);
    m_dmeTextColor = QColor(255, 255, 255);

    m_originalPixPerDev = 52.5f;
    m_originalNavCtr = QPointF(150.0f, 150.0f);

    m_originalCrsTextCtr = QPointF(50.0f,  25.0f);
    m_originalHdgTextCtr = QPointF(250.0f,  25.0f);
    m_originalDmeTextCtr = QPointF(250.0f, 275.0f);

    m_originalHeight = 300;
    m_originalWidth = 300;

    m_backZ = 0;
    m_maskZ = 100;
    m_markZ = 200;

    m_brgArrowZ = 60;
    m_crsArrowZ = 70;
    m_crsTextZ = 130;
    m_devBarZ = 50;
    m_devScaleZ = 10;
    m_hdgBugZ = 120;
    m_hdgScaleZ = 110;
    m_hdgTextZ = 130;
    m_dmeTextZ = 130;

    m_crsTextFont.setFamily("Courier");
    m_crsTextFont.setPointSizeF(12.0f);
    m_crsTextFont.setStretch(QFont::Condensed);
    m_crsTextFont.setWeight(QFont::Bold);

    m_hdgTextFont.setFamily("Courier");
    m_hdgTextFont.setPointSizeF(12.0f);
    m_hdgTextFont.setStretch(QFont::Condensed);
    m_hdgTextFont.setWeight(QFont::Bold);

    m_dmeTextFont.setFamily("Courier");
    m_dmeTextFont.setPointSizeF(10.0f);
    m_dmeTextFont.setStretch(QFont::Condensed);
    m_dmeTextFont.setWeight(QFont::Bold);

    reset();
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);
    m_scene->clear();
    init();

    this->setStyleSheet("background:transparent;border:0px");
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

FlightNAV::~FlightNAV()
{
    if (m_scene != 0) {
        m_scene->clear();
        delete m_scene;
        m_scene = 0;
    }

    reset();
}

void FlightNAV::reinit()
{
    if (m_scene) {
        m_scene->clear();
        init();
    }
}

void FlightNAV::update()
{
    updateView();
    m_devBarDeltaX_old = m_devBarDeltaX_new;
    m_devBarDeltaY_old = m_devBarDeltaY_new;
}

float FlightNAV::getHeading() const
{
    return this->m_heading;
}

void FlightNAV::setHeading(float heading)
{
    m_heading = heading;
    while (m_heading <   0.0f) {
        m_heading += 360.0f;
    }
    while (m_heading > 360.0f) {
        m_heading -= 360.0f;
    }
    this->update();
}

float FlightNAV::getHeadingBug() const
{
    return this->m_headingBug;
}

void FlightNAV::setHeadingBug(float headingBug)
{
    m_headingBug = headingBug;
    while (m_headingBug <   0.0f) {
        m_headingBug += 360.0f;
    }
    while (m_headingBug > 360.0f) {
        m_headingBug -= 360.0f;
    }
    this->update();
}

float FlightNAV::getCourse() const
{
    return this->m_course;
}

void FlightNAV::setCourse(float course)
{
    m_course = course;
    while (m_course <   0.0f) {
        m_course += 360.0f;
    }
    while (m_course > 360.0f) {
        m_course -= 360.0f;
    }
    this->update();
}

float FlightNAV::getBearing() const
{
    return this->m_bearing;
}

void FlightNAV::setBearing(float bearing)
{
    m_bearing = bearing;
    while (m_bearing < 0.0f) {
        m_bearing += 360.0f;
    }
    while (m_bearing > 360.0f) {
        m_bearing -= 360.0f;
    }
    this->update();
}

bool FlightNAV::getBearingVisible() const
{
    return this->m_bearingVisible;
}

void FlightNAV::setBearingVisible(bool visible)
{
    m_bearingVisible = visible;
    this->update();
}

float FlightNAV::getDeviation() const
{
    return this->m_deviation;
}

void FlightNAV::setDeviation(float deviation)
{
    m_deviation = deviation;
    if (m_deviation < -1.0f) {
        m_deviation = -1.0f;
    }
    if (m_deviation >  1.0f) {
        m_deviation =  1.0f;
    }
    this->update();
}

bool FlightNAV::getDeviationVisible() const
{
    return this->m_deviationVisible;
}

void FlightNAV::setDeviationVisible(bool visible)
{
    m_deviationVisible = visible;
    this->update();
}

float FlightNAV::getDistance() const
{
    return this->m_distance;
}

void FlightNAV::setDistance(float distance)
{
    m_distance = fabs(distance);
    this->update();
}

bool FlightNAV::getDistanceVisible() const
{
    return this->m_distanceVisible;
}

void FlightNAV::setDistanceVisible(bool visible)
{
    m_distanceVisible = visible;
    this->update();
}

QSize FlightNAV::sizeHint() const
{
    return QSize(300, 300);
}

QSize FlightNAV::minimumSizeHint() const
{
    return QSize(30, 30);
}

void FlightNAV::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    reinit();
}

void FlightNAV::init()
{
#ifndef noxmlsvg
    m_scaleX = (float)width()  / (float)m_originalWidth;
    m_scaleY = (float)height() / (float)m_originalHeight;

    m_itemBack = new QGraphicsSvgItem(":/svg/flight/nav_back.svg");
    m_itemBack->setCacheMode(QGraphicsItem::NoCache);
    m_itemBack->setZValue(m_backZ);
    m_itemBack->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_scene->addItem(m_itemBack);

    m_itemMask = new QGraphicsSvgItem(":/svg/flight/nav_mask.svg");
    m_itemMask->setCacheMode(QGraphicsItem::NoCache);
    m_itemMask->setZValue(m_maskZ);
    m_itemMask->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_scene->addItem(m_itemMask);

    m_itemMark = new QGraphicsSvgItem(":/svg/flight/nav_mark.svg");
    m_itemMark->setCacheMode(QGraphicsItem::NoCache);
    m_itemMark->setZValue(m_markZ);
    m_itemMark->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_scene->addItem(m_itemMark);

    m_itemBrgArrow = new QGraphicsSvgItem(":/svg/flight/nav_brg_arrow.svg");
    m_itemBrgArrow->setCacheMode(QGraphicsItem::NoCache);
    m_itemBrgArrow->setZValue(m_brgArrowZ);
    m_itemBrgArrow->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemBrgArrow->setTransformOriginPoint(m_originalNavCtr);
    m_scene->addItem(m_itemBrgArrow);

    m_itemCrsArrow = new QGraphicsSvgItem(":/svg/flight/nav_crs_arrow.svg");
    m_itemCrsArrow->setCacheMode(QGraphicsItem::NoCache);
    m_itemCrsArrow->setZValue(m_crsArrowZ);
    m_itemCrsArrow->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemCrsArrow->setTransformOriginPoint(m_originalNavCtr);
    m_scene->addItem(m_itemCrsArrow);

    m_itemDevBar = new QGraphicsSvgItem(":/svg/flight/nav_dev_bar.svg");
    m_itemDevBar->setCacheMode(QGraphicsItem::NoCache);
    m_itemDevBar->setZValue(m_devBarZ);
    m_itemDevBar->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemDevBar->setTransformOriginPoint(m_originalNavCtr);
    m_scene->addItem(m_itemDevBar);

    m_itemDevScale = new QGraphicsSvgItem(":/svg/flight/nav_dev_scale.svg");
    m_itemDevScale->setCacheMode(QGraphicsItem::NoCache);
    m_itemDevScale->setZValue(m_devScaleZ);
    m_itemDevScale->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemDevScale->setTransformOriginPoint(m_originalNavCtr);
    m_scene->addItem(m_itemDevScale);

    m_itemHdgBug = new QGraphicsSvgItem(":/svg/flight/nav_hdg_bug.svg");
    m_itemHdgBug->setCacheMode(QGraphicsItem::NoCache);
    m_itemHdgBug->setZValue(m_hdgBugZ);
    m_itemHdgBug->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemHdgBug->setTransformOriginPoint(m_originalNavCtr);
    m_scene->addItem(m_itemHdgBug);

    m_itemHdgScale = new QGraphicsSvgItem(":/svg/flight/nav_hdg_scale.svg");
    m_itemHdgScale->setCacheMode(QGraphicsItem::NoCache);
    m_itemHdgScale->setZValue(m_hdgScaleZ);
    m_itemHdgScale->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemHdgScale->setTransformOriginPoint(m_originalNavCtr);
    m_scene->addItem(m_itemHdgScale);

    m_itemCrsText = new QGraphicsTextItem(QString("CRS 999"));
    m_itemCrsText->setCacheMode(QGraphicsItem::NoCache);
    m_itemCrsText->setZValue(m_crsTextZ);
    m_itemCrsText->setDefaultTextColor(m_crsTextColor);
    m_itemCrsText->setFont(m_crsTextFont);
    m_itemCrsText->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemCrsText->moveBy(m_scaleX * (m_originalCrsTextCtr.x() - m_itemCrsText->boundingRect().width()  / 2.0f),
                          m_scaleY * (m_originalCrsTextCtr.y() - m_itemCrsText->boundingRect().height() / 2.0f));
    m_scene->addItem(m_itemCrsText);

    m_itemHdgText = new QGraphicsTextItem(QString("HDG 999"));
    m_itemHdgText->setCacheMode(QGraphicsItem::NoCache);
    m_itemHdgText->setZValue(m_hdgTextZ);
    m_itemHdgText->setDefaultTextColor(m_hdgTextColor);
    m_itemHdgText->setFont(m_hdgTextFont);
    m_itemHdgText->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemHdgText->moveBy(m_scaleX * (m_originalHdgTextCtr.x() - m_itemHdgText->boundingRect().width()  / 2.0f),
                          m_scaleY * (m_originalHdgTextCtr.y() - m_itemHdgText->boundingRect().height() / 2.0f));
    m_scene->addItem(m_itemHdgText);

    m_itemDmeText = new QGraphicsTextItem(QString("99.9 NM"));
    m_itemDmeText->setCacheMode(QGraphicsItem::NoCache);
    m_itemDmeText->setZValue(m_dmeTextZ);
    m_itemDmeText->setDefaultTextColor(m_dmeTextColor);
    m_itemDmeText->setFont(m_dmeTextFont);
    m_itemDmeText->setTransform(QTransform::fromScale(m_scaleX, m_scaleY), true);
    m_itemDmeText->moveBy(m_scaleX * (m_originalDmeTextCtr.x() - m_itemDmeText->boundingRect().width()  / 2.0f),
                          m_scaleY * (m_originalDmeTextCtr.y() - m_itemDmeText->boundingRect().height() / 2.0f));
    m_scene->addItem(m_itemDmeText);

    updateView();
#endif
}

void FlightNAV::reset()
{
    m_itemBrgArrow = 0;
    m_itemCrsArrow = 0;
    m_itemDevBar   = 0;
    m_itemDevScale = 0;
    m_itemHdgBug   = 0;
    m_itemHdgScale = 0;

    m_itemCrsText = 0;
    m_itemHdgText = 0;
    m_itemDmeText = 0;

    m_heading    = 0.0f;
    m_headingBug = 0.0f;
    m_course     = 0.0f;
    m_bearing    = 0.0f;
    m_deviation  = 0.0f;
    m_distance   = 0.0f;

    m_bearingVisible   = true;
    m_deviationVisible = true;
    m_distanceVisible  = true;

    m_devBarDeltaX_new = 0.0f;
    m_devBarDeltaX_old = 0.0f;
    m_devBarDeltaY_new = 0.0f;
    m_devBarDeltaY_old = 0.0f;
}

void FlightNAV::updateView()
{
#ifndef noxmlsvg
    m_scaleX = (float)width()  / (float)m_originalWidth;
    m_scaleY = (float)height() / (float)m_originalHeight;

    m_itemCrsArrow->setRotation(-m_heading + m_course);
    m_itemHdgBug->setRotation(-m_heading + m_headingBug);
    m_itemHdgScale->setRotation(-m_heading);

    if (m_bearingVisible) {
        m_itemBrgArrow->setVisible(true);
        m_itemBrgArrow->setRotation(-m_heading + m_bearing);
    } else {
        m_itemBrgArrow->setVisible(false);
    }

    if (m_deviationVisible) {
        m_itemDevBar->setVisible(true);
        m_itemDevScale->setVisible(true);

        float angle_deg = -m_heading + m_course;
        float angle_rad = M_PI * angle_deg / 180.0f;

        float sinAngle = sin(angle_rad);
        float cosAngle = cos(angle_rad);

        m_itemDevBar->setRotation(angle_deg);
        m_itemDevScale->setRotation(angle_deg);

        float delta  = m_originalPixPerDev * m_deviation;

        m_devBarDeltaX_new = m_scaleX * delta * cosAngle;
        m_devBarDeltaY_new = m_scaleY * delta * sinAngle;

        m_itemDevBar->moveBy(m_devBarDeltaX_new - m_devBarDeltaX_old, m_devBarDeltaY_new - m_devBarDeltaY_old);
    } else {
        m_itemDevBar->setVisible(false);
        m_itemDevScale->setVisible(false);

        m_devBarDeltaX_new = m_devBarDeltaX_old;
        m_devBarDeltaY_new = m_devBarDeltaY_old;
    }

    m_itemCrsText->setPlainText(QString("CRS %1").arg(m_course, 3, 'f', 0, QChar('0')));
    m_itemHdgText->setPlainText(QString("HDG %1").arg(m_headingBug, 3, 'f', 0, QChar('0')));

    if (m_distanceVisible) {
        m_itemDmeText->setVisible(true);
        m_itemDmeText->setPlainText(QString("%1 NM").arg(m_distance, 5, 'f', 1, QChar(' ')));
    } else {
        m_itemDmeText->setVisible(false);
    }

    m_scene->update();
    centerOn(width() / 2.0f, height() / 2.0f);
#endif
}
