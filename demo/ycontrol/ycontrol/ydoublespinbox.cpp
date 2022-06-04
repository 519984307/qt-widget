#pragma execution_character_set("utf-8")

#include "ydoublespinbox.h"
#include "qlayout.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include "qdebug.h"

YDoubleSpinBox::YDoubleSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
    //将翻页按钮隐藏
    this->setButtonSymbols(QAbstractSpinBox::NoButtons);

    //将文本框拿出来
    QList<QLineEdit *> edits = this->findChildren<QLineEdit *>();
    edit = edits.first();
    edit->setFrame(true);
    edit->setAlignment(Qt::AlignCenter);
    edit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    btnSize = 30;

    //标题
    labTitle = new QLabel;
    labTitle->setAlignment(Qt::AlignCenter);
    labTitle->setText("标题");

    //单位
    labUnit = new QLabel;
    labUnit->setAlignment(Qt::AlignCenter);
    labUnit->setText("单位");

    QPushButton *btnDown = new QPushButton;
    btnDown->setObjectName("qt_spinbox_btnDown");
    connect(btnDown, SIGNAL(clicked(bool)), this, SLOT(stepDown()));
    btnDown->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    QPushButton *btnUp = new QPushButton;
    btnUp->setObjectName("qt_spinbox_btnUp");
    connect(btnUp, SIGNAL(clicked(bool)), this, SLOT(stepUp()));
    btnUp->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addStretch(1);

    //可以自行调整顺序组合摆放控件位置
    layout->addWidget(labTitle);
    layout->addWidget(edit);
    layout->addWidget(labUnit);
    layout->addWidget(btnDown);
    layout->addWidget(btnUp);

    layout->setContentsMargins(3, 3, 3, 3);
    this->setLayout(layout);
    this->initStyle();
}

void YDoubleSpinBox::resizeEvent(QResizeEvent *)
{

}

void YDoubleSpinBox::paintEvent(QPaintEvent *)
{
}

void YDoubleSpinBox::initStyle()
{
    //设置按钮样式
    QStringList list;
    //list << QString("QAbstractSpinBox{border:2px solid #7C7C96;background:#FF0000;}");
    list << QString("QPushButton{min-width:%1px;max-width:%1px;min-height:%1px;max-height:%1px;}").arg(btnSize);
    list << QString("QPushButton{border-image:url(:/image/ycontrol/spinBoxButton_normal.png);}");
    list << QString("QPushButton:pressed{border-image:url(:/image/ycontrol/spinBoxButton_select.png);}");
    list << QString("#qt_spinbox_btnDown{image:url(:/image/ycontrol/spinBoxButton_normal_minus.png)}");
    list << QString("#qt_spinbox_btnDown:pressed{image:url(:/image/ycontrol/spinBoxButton_select_minus.png)}");
    list << QString("#qt_spinbox_btnUp{image:url(:/image/ycontrol/spinBoxButton_normal_plus.png)}");
    list << QString("#qt_spinbox_btnUp:pressed{image:url(:/image/ycontrol/spinBoxButton_select_plus.png)}");
    this->setStyleSheet(list.join(""));
}

int YDoubleSpinBox::getBtnSize() const
{
    return this->btnSize;
}

QString YDoubleSpinBox::getTitle() const
{
    return labTitle->text();
}

QString YDoubleSpinBox::getUnit() const
{
    return labUnit->text();
}

QSize YDoubleSpinBox::sizeHint() const
{
    return QSize(230, 40);
}

QSize YDoubleSpinBox::minimumSizeHint() const
{
    return QSize(50, 20);
}

void YDoubleSpinBox::setBtnSize(int btnSize)
{
    this->btnSize = btnSize;
    this->initStyle();
}

void YDoubleSpinBox::setTitle(const QString &title)
{
    labTitle->setText(title);
}

void YDoubleSpinBox::setUnit(const QString &unit)
{
    labUnit->setText(unit);
}
