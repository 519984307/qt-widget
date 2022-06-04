#include "squarelayout.h"

SquareLayout::SquareLayout(QWidget *parent, int spacing) : QLayout(parent)
{
    init(spacing);
}

SquareLayout::SquareLayout(int spacing) : QLayout(0)
{
    init(spacing);
}

SquareLayout::~SquareLayout()
{
    if (m_item) {
        delete m_item;
    }
    m_item = 0;

    if (m_rectLast) {
        delete m_rectLast;
    }
    m_rectLast = 0;
    if (m_geometry) {
        delete m_geometry;
    }
    m_geometry = 0;
}

void SquareLayout::addItem(QLayoutItem *item)
{
    if (!hasItem()) {
        replaceItem(item);
    }
}

void SquareLayout::addWidget(QWidget *widget)
{
    if (!hasItem()) {
        replaceItem(new QWidgetItem(widget));
    }
}

int SquareLayout::count() const
{
    if (hasItem()) {
        return 1;
    }

    return 0;
}

Qt::Orientations SquareLayout::expandingDirections() const
{
    return (Qt::Horizontal | Qt::Vertical);
}

QRect SquareLayout::geometry()
{
    return (QRect)(*m_geometry);
}

bool SquareLayout::hasHeightForWidth() const
{
    return false;
}

bool SquareLayout::hasItem() const
{
    return (m_item != 0);
}

QLayoutItem *SquareLayout::itemAt(int index) const
{
    if (index == 0) {
        if (hasItem()) {
            return m_item;
        }
    }

    return 0;
}

QSize SquareLayout::minimumSize() const
{
    return m_item->minimumSize();
}

QLayoutItem *SquareLayout::replaceItem(QLayoutItem *item)
{
    QLayoutItem *tempItem = 0;
    if (hasItem()) {
        tempItem = m_item;
    }

    m_item = item;
    setGeometry(*m_geometry);
    return tempItem;
}

void SquareLayout::setGeometry(const QRect &rect)
{
    if (!hasItem() || areRectsEqual(*m_rectLast, rect)) {
        return;
    }

    setRectLast(rect);
    QSize  properSize  = calculateProperSize(rect.size());
    QPoint centerPoint = calculateCenterPnt(rect.size(), properSize);

    m_item->setGeometry(QRect(centerPoint, properSize));
    QRect *tempRect = m_geometry;
    m_geometry = new QRect(centerPoint, properSize);

    delete tempRect;
    QLayout::setGeometry(*m_geometry);
}

QSize SquareLayout::sizeHint() const
{
    return m_item->minimumSize();
}

QLayoutItem *SquareLayout::take()
{
    QLayoutItem *tempItem = 0;
    if (hasItem()) {
        tempItem = m_item;
        m_item = 0;
    }

    return tempItem;
}

QLayoutItem *SquareLayout::takeAt(int index)
{
    if (index == 0) {
        return take();
    }

    return 0;
}

bool SquareLayout::areRectsEqual(const QRect &rect_1, const QRect &rect_2) const
{
    bool result = false;
    if ((rect_1.x() == rect_2.x())
        && (rect_1.y() == rect_2.y())
        && (rect_1.height() == rect_2.height())
        && (rect_1.width() == rect_2.width())) {
        result = true;
    }

    return result;
}

QPoint SquareLayout::calculateCenterPnt(QSize fromSize, QSize itemSize) const
{
    QPoint centerPoint;
    if ((fromSize.width() - fromSize.width() / 2.0 - itemSize.width() / 2.0) > 0.0) {
        centerPoint.setX(fromSize.width() - fromSize.width() / 2.0 - itemSize.width() / 2.0);
    }

    if ((fromSize.height() - fromSize.height() / 2.0 - itemSize.height() / 2.0) > 0.0) {
        centerPoint.setY(fromSize.height() - fromSize.height() / 2.0 - itemSize.height() / 2.0);
    }

    return centerPoint;
}

QSize SquareLayout::calculateProperSize(QSize fromSize) const
{
    QSize resultSize;
    int height = fromSize.height();
    int width = fromSize.width();
    int margin = contentsMargins().left();
    if (height < width) {
        resultSize.setHeight(height - margin);
        resultSize.setWidth(height - margin);
    } else {
        resultSize.setHeight(width - margin);
        resultSize.setWidth(width - margin);
    }

    return resultSize;
}

void SquareLayout::init(int spacing)
{
    m_item = 0;
    m_rectLast = new QRect(0, 0, 0, 0);
    m_geometry = new QRect(0, 0, 0, 0);
    setSpacing(spacing);
}

void SquareLayout::setRectLast(const QRect &rect)
{
    QRect *tempRect = m_rectLast;
    m_rectLast = new QRect(rect.topLeft(), rect.size());
    delete tempRect;
}
