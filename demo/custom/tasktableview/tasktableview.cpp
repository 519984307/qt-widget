#pragma execution_character_set("utf-8")

#include "tasktableview.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmenu.h"
#include "qheaderview.h"
#include "qframe.h"
#include "qdebug.h"

TaskModel::TaskModel(QObject *parent) : QAbstractTableModel(parent)
{
    row = 0;
    column = 0;

    for (int i = 0; i < 24; ++i) {
        horizontalHeader << QString::number(i);
        horizontalHeader << QString::number((float)i + 0.5);
    }

    verticalHeader << "星期一" << "星期二" << "星期三" << "星期四" << "星期五" << "星期六" << "星期日";
}

TaskModel::~TaskModel()
{

}

int TaskModel::rowCount(const QModelIndex &) const
{
    return row;
}

int TaskModel::columnCount(const QModelIndex &) const
{
    return column;
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    int row = index.row();
    int column = index.column();

    switch (role) {
        case Qt::ToolTipRole: {
            if (row > 0 && column > 0) {
                return verticalHeader.at(row - 1) + " " + horizontalHeader.at(column - 1);
            }
            break;
        }
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        case Qt::UserRole: {
            if (column == 0 && row > 0 && row <= verticalHeader.size()) {
                return verticalHeader.at(row - 1);
            } else if (row == 0 && column > 0 && column <= horizontalHeader.size()) {
                return horizontalHeader.at(column - 1);
            }
            break;
        }
        default:
            return QVariant();
    }

    return QVariant();
}

Qt::ItemFlags TaskModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index);
}

void TaskModel::setColumnCount(int column)
{
    this->column = column;
}

void TaskModel::setRowCount(int row)
{
    this->row = row;
}

void TaskModel::internalUpdate()
{
    QModelIndex begin = index(0, 0);
    QModelIndex end = index(row, column);
    emit dataChanged(begin, end);
    emit headerDataChanged(Qt::Vertical, 0, row - 1);
    emit headerDataChanged(Qt::Horizontal, 0, column - 1);
}

const int shadow = 2;
TaskDelegate::TaskDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{
    widget = parent;

    bgColor = QColor(255, 255, 255);
    gridColor = QColor(150, 150, 150);

    headerBgColor = QColor(220, 220, 220);
    headerTextColor = QColor(60, 60, 60);    

    normalColor = QColor(140, 143, 145);
    selectColor = QColor(84, 111, 198);
}

TaskDelegate::~TaskDelegate()
{

}

void TaskDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);
    if (option.state.testFlag(QStyle::State_HasFocus)) {
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
    }

    QStyledItemDelegate::paint(painter, viewOption, index);

    int row = index.row();
    int column = index.column();
    QRect rect = viewOption.rect;

    //第一行列作为标题特殊处理
    if (row == 0 || column == 0) {
        painter->save();
        painter->setPen(QPen(Qt::NoPen));
        painter->setBrush(headerBgColor);
        painter->drawRect(rect);
        if (row == 0 && column == 0) {
            painter->setPen(gridColor);
            painter->setBrush(Qt::NoBrush);
            painter->drawLine(rect.topLeft(), rect.bottomRight());
        }
        painter->restore();
    } else {
        painter->save();
        painter->setPen(QPen(Qt::NoPen));
        painter->setBrush(bgColor);
        painter->drawRect(rect);
        painter->restore();
    }

    //居中绘制行标题列标题
    if ((column == 0 && row > 0) || (row == 0 && column > 0)) {
        painter->save();
        painter->setPen(headerTextColor);
        painter->setBrush(Qt::NoBrush);
        QTextOption option(Qt::AlignHCenter | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAnywhere);
        QString text = index.data(Qt::UserRole).toString();
        QRect textrect = rect.adjusted(4, 0, 0, 0);
        painter->drawText(textrect, text, option);
        painter->restore();
    }

    //绘制表格线条
    if (row > 0) {
        painter->save();
        painter->setPen(gridColor);
        painter->setBrush(Qt::NoBrush);
        painter->drawLine(rect.x(), rect.y(), rect.x() + rect.width(), rect.y());
        painter->restore();
    }
    if (column > 0 && column % 2 == 1) {
        painter->save();
        painter->setPen(gridColor);
        painter->setBrush(Qt::NoBrush);
        painter->drawLine(rect.x(), rect.y(), rect.x(), rect.y() + rect.height());
        painter->restore();
    }

    //绘制选中单元格方块
    if (column > 0 && row > 0) {
        QRect drawrect;
        if (column % 2 == 1) {
            drawrect = QRect(rect.x() + 1, rect.y() + 1, rect.width() - 2, rect.height() - 2);
        } else {
            drawrect = QRect(rect.x(), rect.y() + 1, rect.width() - 1, rect.height() - 2);
        }

        //通过设置不同的透明度呈现立体感
        painter->save();
        painter->setPen(QPen(Qt::NoPen));
        if (option.state.testFlag(QStyle::State_Selected)) {
            QColor color = selectColor;
            color.setAlpha(100);
            painter->setBrush(color);
            painter->drawRect(drawrect.x(), drawrect.y() + drawrect.height() - shadow, drawrect.width() - shadow, shadow);
            painter->drawRect(drawrect.x() + drawrect.width() - shadow, drawrect.y(), shadow, drawrect.height());
            painter->setBrush(QColor(52, 52, 52, 100));
            painter->drawRect(drawrect.x(), drawrect.y(), drawrect.width(), shadow);
            painter->drawRect(drawrect.x(), drawrect.y(), shadow, drawrect.height());
            color.setAlpha(255);
            painter->setBrush(color);
            painter->drawRect(drawrect.x() + shadow, drawrect.y() + shadow, drawrect.width() - shadow * 2, drawrect.height() - shadow * 2);
        } else {
            QColor color = normalColor;
            color.setAlpha(100);
            painter->setBrush(color);
            painter->drawRect(drawrect.x(), drawrect.y(), drawrect.width(), shadow);
            painter->drawRect(drawrect.x(), drawrect.y() + shadow, shadow, drawrect.height() - shadow);
            painter->setBrush(QColor(52, 52, 52, 100));
            painter->drawRect(drawrect.x(), drawrect.y() + drawrect.height() - shadow, drawrect.width(), shadow);
            painter->drawRect(drawrect.x() + drawrect.width() - shadow, drawrect.y(), shadow, drawrect.height());
            color.setAlpha(255);
            painter->setBrush(color);
            painter->drawRect(drawrect.x() + shadow, drawrect.y() + shadow, drawrect.width() - shadow * 2, drawrect.height() - shadow * 2);
        }
        painter->restore();
    }
}

bool TaskDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    int row = index.row();
    int column = index.column();

    if (event->type() == QEvent::MouseButtonPress) {
        currentIndex = index;
        if (currentIndex.row() == 0 || currentIndex.column() == 0) {
            return true;
        }
    } else if (event->type() == QEvent::MouseMove) {
        if (currentIndex.row() == 0 || currentIndex.column() == 0 || row == 0 || column == 0) {
            return true;
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QColor TaskDelegate::getBgColor() const
{
    return bgColor;
}

void TaskDelegate::setBgColor(const QColor &color)
{
    bgColor = color;
    widget->update();
}

QColor TaskDelegate::getGridColor() const
{
    return gridColor;
}

void TaskDelegate::setGridColor(const QColor &color)
{
    gridColor = color;
    widget->update();
}

QColor TaskDelegate::getHeaderTextColor() const
{
    return headerTextColor;
}

void TaskDelegate::setHeaderTextColor(const QColor &color)
{
    headerTextColor = color;
    widget->update();
}

QColor TaskDelegate::getHeaderBgColor() const
{
    return headerBgColor;
}

void TaskDelegate::setHeaderBgColor(const QColor &color)
{
    headerBgColor = color;
    widget->update();
}

QColor TaskDelegate::getNormalColor() const
{
    return normalColor;
}

void TaskDelegate::setNormalColor(const QColor &color)
{
    normalColor = color;
    widget->update();
}

QColor TaskDelegate::getSelectColor() const
{
    return selectColor;
}

void TaskDelegate::setSelectColor(const QColor &color)
{
    selectColor = color;
    widget->update();
}

TaskTableView::TaskTableView(QWidget *parent) : QTableView(parent)
{
    this->initForm();
    this->initMenu();
}

void TaskTableView::resizeEvent(QResizeEvent *)
{
    updateGridItem();
}

void TaskTableView::contextMenuEvent(QContextMenuEvent *)
{
    menu->exec(QCursor::pos());
}

void TaskTableView::initForm()
{
    //设置数据模型
    taskModel = new TaskModel(this);
    taskModel->setColumnCount(49);
    taskModel->setRowCount(8);
    setModel(taskModel);

    //设置自定义委托控制样式
    taskDelegate = new TaskDelegate(this);
    setItemDelegate(taskDelegate);

    this->setShowGrid(false);
    this->setWordWrap(true);
    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setStretchLastSection(true);
    this->horizontalHeader()->setStretchLastSection(true);
    this->setFrameShape(QFrame::NoFrame);
    this->setSelectionMode(QAbstractItemView::MultiSelection);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
#else
    this->verticalHeader()->setResizeMode(QHeaderView::Fixed);
    this->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
#endif

    //合并单元格
    for (int i = 1; i < 48; i += 2) {
        this->setSpan(0, i, 1, 2);
    }

    //设置默认尺寸
    this->horizontalHeader()->setDefaultSectionSize(12);
    this->horizontalHeader()->setMinimumSectionSize(12);
    this->setRowHeight(0, 25);
    this->setColumnWidth(0, 60);
}

void TaskTableView::initMenu()
{
    menu = new QMenu(this);
    QAction *actionAll = menu->addAction("全选");
    QAction *actionInvert = menu->addAction("反选");
    QAction *actionBack = menu->addAction("撤销改变");
    QAction *actionClear = menu->addAction("清空选中");
    connect(actionAll, SIGNAL(triggered(bool)), this, SLOT(doAction()));
    connect(actionInvert, SIGNAL(triggered(bool)), this, SLOT(doAction()));
    connect(actionBack, SIGNAL(triggered(bool)), this, SLOT(doAction()));
    connect(actionClear, SIGNAL(triggered(bool)), this, SLOT(doAction()));
}

void TaskTableView::doAction()
{
    QAction *action = (QAction *)sender();
    QString text = action->text();
    if (text == "全选") {
        QItemSelection selection;
        QModelIndex tl = this->model()->index(1, 1);
        QModelIndex br = this->model()->index(this->model()->rowCount() - 1, this->model()->columnCount() - 1);
        selection.append(QItemSelectionRange(tl, br));
        this->selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect);
        onSelectChanged();
    } else if (text == "反选") {
        QItemSelection allselection;
        QModelIndex tl = this->model()->index(1, 1);
        QModelIndex br = this->model()->index(this->model()->rowCount() - 1, this->model()->columnCount() - 1);
        allselection.append(QItemSelectionRange(tl, br));

        QItemSelection listSelcetion = selectionModel()->selection();
        this->selectionModel()->select(allselection, QItemSelectionModel::ClearAndSelect);
        this->selectionModel()->select(listSelcetion, QItemSelectionModel::Deselect);
        onSelectChanged();
    } else if (text == "撤销改变") {
        if (listSelection.size() > 0) {
            QItemSelection selection = listSelection.last();
            listSelection.pop_back();
            this->selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect);
            currentSelection = this->selectionModel()->selection();
        }
    } else if (text == "清空选中") {
        this->selectionModel()->clear();
        onSelectChanged();
    }
}

void TaskTableView::updateGridItem()
{
    int rowCount = this->model()->rowCount() - 1;
    int toalHeight = this->height() - this->rowHeight(0) - 4;
    double curheightDouble = toalHeight * 1.0 / rowCount;
    double spaceHeight = (curheightDouble - (int)curheightDouble) * rowCount;
    for (int i = 1; i <= rowCount; i++) {
        int tmpheight = 0;
        if (spaceHeight >= 0) {
            tmpheight = 1;
            spaceHeight -= 1;
        }
        this->setRowHeight(i, curheightDouble + tmpheight);
    }

    int columnCount = this->model()->columnCount() - 1;
    int totalWidth = this->width() - this->columnWidth(0) - 3;
    double curWidthDouble = totalWidth * 1.0 / columnCount;
    double spaceWidth = (curWidthDouble - (int)curWidthDouble) * columnCount;
    for (int i = 1; i <= columnCount; i++) {
        int tmpWidth = 0;
        if (spaceWidth >= 0) {
            tmpWidth = 1;
            spaceWidth -= 1;
        }
        this->setColumnWidth(i, curWidthDouble + tmpWidth);
    }
}

void TaskTableView::onSelectChanged()
{
    listSelection.push_back(currentSelection);
    currentSelection = this->selectionModel()->selection();
}

QSize TaskTableView::sizeHint() const
{
    return QSize(600, 400);
}

QSize TaskTableView::minimumSizeHint() const
{
    return QSize(100, 60);
}

QColor TaskTableView::getBgColor() const
{
    return taskDelegate->getBgColor();
}

void TaskTableView::setBgColor(const QColor &color)
{
    taskDelegate->setBgColor(color);
}

QColor TaskTableView::getGridColor() const
{
    return taskDelegate->getGridColor();
}

void TaskTableView::setGridColor(const QColor &color)
{
    taskDelegate->setGridColor(color);
}

QColor TaskTableView::getHeaderBgColor() const
{
    return taskDelegate->getHeaderBgColor();
}

void TaskTableView::setHeaderBgColor(const QColor &color)
{
    taskDelegate->setHeaderBgColor(color);
}

QColor TaskTableView::getHeaderTextColor() const
{
    return taskDelegate->getHeaderTextColor();
}

void TaskTableView::setHeaderTextColor(const QColor &color)
{
    taskDelegate->setHeaderTextColor(color);
}

QColor TaskTableView::getNormalColor() const
{
    return taskDelegate->getNormalColor();
}

void TaskTableView::setNormalColor(const QColor &color)
{
    taskDelegate->setNormalColor(color);
}

QColor TaskTableView::getSelectColor() const
{
    return taskDelegate->getSelectColor();
}

void TaskTableView::setSelectColor(const QColor &color)
{
    taskDelegate->setSelectColor(color);
}
