#pragma execution_character_set("utf-8")

#include "navpage.h"
#include "qstyle.h"
#include "qfontdatabase.h"
#include "qboxlayout.h"
#include "qlayoutitem.h"
#include "qlabel.h"
#include "qspinbox.h"
#include "qpushbutton.h"
#include "qbuttongroup.h"
#include "qdebug.h"

NavPage::NavPage(QWidget *parent) : QWidget(parent)
{
    showStyle = true;
    showLabInfo = false;
    showGoPage = false;
    navPosition = NavPosition_Center;

    minWidth = 40;
    pageButtonCount = 5;
    spacing = 6;
    fontSize = 15;

    borderWidth = 0;
    borderRadius = 5;
    borderColor = "#F7F7FC";

    normalBgColor = "#F7F7FC";
    normalTextColor = "#737391";
    hoverBgColor = "#FC5531";
    hoverTextColor = "#FFFFFD";
    pressedBgColor = "#FC5531";
    pressedTextColor = "#FFFFFD";
    checkedBgColor = "#FC5531";
    checkedTextColor = "#FFFFFD";

    //判断图形字体是否存在,不存在则加入
    QFontDatabase fontDb;
    if (!fontDb.families().contains("FontAwesome")) {
        int fontId = fontDb.addApplicationFont(":/font/fontawesome-webfont.ttf");
        QStringList fontName = fontDb.applicationFontFamilies(fontId);
        if (fontName.count() == 0) {
            qDebug() << "load fontawesome-webfont.ttf error";
        }
    }

    if (fontDb.families().contains("FontAwesome")) {
        iconFont = QFont("FontAwesome");
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,0))
        iconFont.setHintingPreference(QFont::PreferNoHinting);
#endif
    }

    layout = 0;
    spacerLeft = 0;
    spacerRight = 0;

    labInfo = 0;
    spinbox = 0;
    btnGoPage = 0;

    this->initStyle();
    this->addBtnMove();
    this->addBtnPage();
    this->addBtnAll();
}

void NavPage::initStyle()
{
    if (!this->showStyle) {
        return;
    }

    QStringList list;
    list << QString("*{font:%1px;}").arg(fontSize);
    list << QString("QLabel{qproperty-alignment:AlignCenter;}");
    list << QString("QPushButton{border-radius:%1px;border:%2px solid %3;}")
         .arg(borderRadius).arg(borderWidth).arg(borderColor.name());

    list << QString("QPushButton{background-color:%1;color:%2;}")
         .arg(normalBgColor.name()).arg(normalTextColor.name());
    list << QString("QPushButton:hover{background-color:%1;color:%2;}")
         .arg(hoverBgColor.name()).arg(hoverTextColor.name());
    list << QString("QPushButton:pressed{background-color:%1;color:%2;}")
         .arg(pressedBgColor.name()).arg(pressedTextColor.name());
    list << QString("QPushButton:checked{background-color:%1;color:%2;}")
         .arg(checkedBgColor.name()).arg(checkedTextColor.name());
    //禁用状态将颜色调淡
    list << QString("QPushButton:disabled{color:rgba(%1,%2,%3,100);}")
         .arg(normalTextColor.red()).arg(normalTextColor.green()).arg(normalTextColor.blue());
    this->setStyleSheet(list.join(""));
}

void NavPage::addBtnMove()
{
    qDeleteAll(btnMove);
    btnMove.clear();

    //先生成 第一页 上一页 下一页 末一页 四个按钮
    QList<QString> listName;
    listName << "pageFirst" << "pagePrevious" << "pageNext" << "pageLast";
    QList<int> listText;
    listText << 0xf049 << 0xf04a << 0xf04e << 0xf050;

    int count = listName.count();
    for (int i = 0; i < count; ++i) {
        QPushButton *btn = new QPushButton;
        btn->setFont(iconFont);
        btn->setMinimumWidth(minWidth);
        btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        btn->setObjectName(listName.at(i));
        btn->setText((QChar)listText.at(i));
        btnMove << btn;
    }
}

void NavPage::addBtnPage()
{
    qDeleteAll(btnPage);
    btnPage.clear();

    //放入按钮分组自动形成选中排斥效果
    QButtonGroup *btnGroup = new QButtonGroup(this);
    //生成中间页码按钮
    for (int i = 1; i <= pageButtonCount; ++i) {
        QPushButton *btn = new QPushButton;
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(btnClicked()));
        btn->setCheckable(true);
        btnGroup->addButton(btn);
        btn->setMinimumWidth(minWidth);
        btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        btn->setObjectName(QString("page%1").arg(i));
        btn->setText(QString("%1").arg(i));
        btnPage << btn;
    }

    btnPage.first()->setChecked(true);
}

void NavPage::addBtnAll()
{
    //新建左右布局
    if (layout == 0) {
        layout = new QHBoxLayout;
        layout->setContentsMargins(6, 6, 6, 6);
        this->setLayout(layout);
    }

    //实例化左侧右侧弹簧
    if (spacerLeft == 0) {
        spacerLeft = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    }
    if (spacerRight == 0) {
        spacerRight = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    }

    //居中对齐或者右对齐则需要在左侧插入弹簧
    if (navPosition == NavPosition_Center || navPosition == NavPosition_Right) {
        layout->addItem(spacerLeft);
    }

    //添加翻页提示信息
    if (labInfo == 0) {
        labInfo = new QLabel;
        labInfo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(labInfo);
        labInfo->setVisible(showLabInfo);
    }

    //添加 第一页 上一页
    layout->addWidget(btnMove.at(0));
    layout->addWidget(btnMove.at(1));

    //循环添加 中间页码
    foreach (QPushButton *btn, btnPage) {
        layout->addWidget(btn);
    }

    //添加 下一页 末一页
    layout->addWidget(btnMove.at(2));
    layout->addWidget(btnMove.at(3));

    //添加 页码微调框
    if (spinbox == 0) {
        spinbox = new QSpinBox;
        spinbox->setRange(1, 1);
        spinbox->setMinimumWidth(minWidth + 20);
        spinbox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);        
    }

    //添加 跳转页码按钮
    if (btnGoPage == 0) {
        btnGoPage = new QPushButton;
        connect(btnGoPage, SIGNAL(clicked(bool)), this, SLOT(btnClicked()));
        btnGoPage->setMinimumWidth(minWidth + 20);
        btnGoPage->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        btnGoPage->setObjectName("pagego");
        btnGoPage->setText("跳转");
    }

    layout->addWidget(spinbox);
    spinbox->setVisible(showGoPage);
    layout->addWidget(btnGoPage);
    btnGoPage->setVisible(showGoPage);

    //居中对齐或者左对齐则需要在右侧插入弹簧
    if (navPosition == NavPosition_Center || navPosition == NavPosition_Left) {
        layout->addItem(spacerRight);
    }

    btnAll.clear();
    btnAll << btnMove << btnPage << btnGoPage;
}

void NavPage::btnClicked()
{
    //直接跳转到对应页码
    QPushButton *btn = (QPushButton *)sender();
    if (btn == btnGoPage) {
        emit selectPage(spinbox->value());
    } else {
        emit selectPage(btn->text().toInt());
    }
}

void NavPage::receivePage(quint32 pageCurrent, quint32 pageCount, quint32 resultCount, quint32 resultCurrent)
{
    //设置页码微调框范围
    spinbox->setRange(1, pageCount);

    //根据页码总数显示隐藏按钮,比如只有1页的时候隐藏其他几个按钮
    for (int i = 0; i < pageButtonCount; ++i) {
        btnPage.at(i)->setVisible(i < pageCount);
        btnPage.at(i)->setText(QString::number(i + 1));
    }

    //重新设置页码按钮的页码
    //计算出中间页码差值,起始页码和结束页码在差值基础上做加减
    int offset = pageButtonCount / 2;
    //偶数页个数需要-1更精确
    if (pageButtonCount % 2 == 0) {
        offset -= 1;
    }

    //总页数大于页码按钮个数才需要处理
    if (pageCount > pageButtonCount) {
        int pageMin = pageCurrent - offset;
        int pageMax = pageCurrent + offset;
        //最小页码不能小于1
        pageMin = pageMin < 1 ? 1 : pageMin;
        //最大页码不能超过总页码数
        pageMax = pageMax > pageCount ? pageCount : pageMax;
        //差值不等于按钮个数重新修改最小值 7-2=5 但是确是6个按钮所以需要-1
        while (pageMax - pageMin != (pageButtonCount - 1)) {
            if (pageMin == 1) {
                break;
            }
            pageMin--;
        }

        //qDebug() << pageButtonCount << offset << pageCurrent << pageMin << pageMax;
        int pageTemp = pageMin;
        for (int i = 0; i < pageButtonCount; ++i) {
            btnPage.at(i)->setText(QString::number(pageTemp));
            pageTemp++;
        }
    }

    //重新选中当前页码按钮
    foreach (QPushButton *btn, btnPage) {
        if (btn->text().toInt() == pageCurrent) {
            btn->setChecked(true);
            break;
        }
    }
}

bool NavPage::getShowStyle() const
{
    return this->showStyle;
}

bool NavPage::getShowLabInfo() const
{
    return this->showLabInfo;
}

bool NavPage::getShowGoPage() const
{
    return this->showGoPage;
}

NavPage::NavPosition NavPage::getNavPosition() const
{
    return this->navPosition;
}

int NavPage::getPageButtonCount() const
{
    return this->pageButtonCount;
}

int NavPage::getSpacing() const
{
    return this->spacing;
}

int NavPage::getFontSize() const
{
    return this->fontSize;
}

int NavPage::getBorderRadius() const
{
    return this->borderRadius;
}

int NavPage::getBorderWidth() const
{
    return this->borderWidth;
}

QColor NavPage::getBorderColor() const
{
    return this->borderColor;
}

QColor NavPage::getNormalBgColor() const
{
    return this->normalBgColor;
}

QColor NavPage::getNormalTextColor() const
{
    return this->normalTextColor;
}

QColor NavPage::getHoverBgColor() const
{
    return this->hoverBgColor;
}

QColor NavPage::getHoverTextColor() const
{
    return this->hoverTextColor;
}

QColor NavPage::getPressedBgColor() const
{
    return this->pressedBgColor;
}

QColor NavPage::getPressedTextColor() const
{
    return this->pressedTextColor;
}

QColor NavPage::getCheckedBgColor() const
{
    return this->checkedBgColor;
}

QColor NavPage::getCheckedTextColor() const
{
    return this->checkedTextColor;
}

QSize NavPage::sizeHint() const
{
    return QSize(500, 50);
}

QSize NavPage::minimumSizeHint() const
{
    return QSize(100, 30);
}

QLabel *NavPage::getLabInfo()
{
    return this->labInfo;
}

QList<QPushButton *> NavPage::getBtnMove()
{
    return this->btnMove;
}

QList<QPushButton *> NavPage::getBtnPage()
{
    return this->btnPage;
}

QList<QPushButton *> NavPage::getBtnAll()
{
    return this->btnAll;
}

void NavPage::setShowStyle(bool showStyle)
{
    if (this->showStyle != showStyle) {
        this->showStyle = showStyle;
        if (this->showStyle) {
            this->initStyle();
        } else {
            //先卸载样式然后重新设置样式为空
            this->style()->unpolish(this);
            this->setStyleSheet("");
            //this->style()->polish(this);
        }
    }
}

void NavPage::setShowLabInfo(bool showLabInfo)
{
    if (this->showLabInfo != showLabInfo) {
        this->showLabInfo = showLabInfo;
        if (labInfo != 0) {
            labInfo->setVisible(showLabInfo);
        }
    }
}

void NavPage::setShowGoPage(bool showGoPage)
{
    if (this->showGoPage != showGoPage) {
        this->showGoPage = showGoPage;
        if (spinbox != 0) {
            spinbox->setVisible(showGoPage);
        }
        if (btnGoPage != 0) {
            btnGoPage->setVisible(showGoPage);
        }
    }
}

void NavPage::setNavPosition(const NavPage::NavPosition &navPosition)
{
    if (this->navPosition != navPosition) {
        this->navPosition = navPosition;
        //先移除布局中的弹簧
        layout->removeItem(spacerLeft);
        layout->removeItem(spacerRight);
        //将所有按钮添加到布局中
        this->addBtnAll();
    }
}

void NavPage::setPageButtonCount(int pageButtonCount)
{
    if (this->pageButtonCount != pageButtonCount && pageButtonCount > 1) {
        this->pageButtonCount = pageButtonCount;
        //先移除布局中所有控件
        foreach (QPushButton *btn, btnAll) {
            layout->removeWidget(btn);
        }

        //重新生成页码按钮
        this->addBtnPage();
        //将所有按钮添加到布局中
        this->addBtnAll();
    }
}

void NavPage::setSpacing(int spacing)
{
    if (this->spacing != spacing) {
        this->spacing = spacing;
        layout->setSpacing(spacing);
    }
}

void NavPage::setFontSize(int fontSize)
{
    if (this->fontSize != fontSize) {
        this->fontSize = fontSize;
        this->initStyle();
    }
}

void NavPage::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        this->initStyle();
    }
}

void NavPage::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        this->initStyle();
    }
}

void NavPage::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        this->initStyle();
    }
}

void NavPage::setNormalBgColor(const QColor &normalBgColor)
{
    if (this->normalBgColor != normalBgColor) {
        this->normalBgColor = normalBgColor;
        this->initStyle();
    }
}

void NavPage::setNormalTextColor(const QColor &normalTextColor)
{
    if (this->normalTextColor != normalTextColor) {
        this->normalTextColor = normalTextColor;
        this->initStyle();
    }
}

void NavPage::setHoverBgColor(const QColor &hoverBgColor)
{
    if (this->hoverBgColor != hoverBgColor) {
        this->hoverBgColor = hoverBgColor;
        this->initStyle();
    }
}

void NavPage::setHoverTextColor(const QColor &hoverTextColor)
{
    if (this->hoverTextColor != hoverTextColor) {
        this->hoverTextColor = hoverTextColor;
        this->initStyle();
    }
}

void NavPage::setPressedBgColor(const QColor &pressedBgColor)
{
    if (this->pressedBgColor != pressedBgColor) {
        this->pressedBgColor = pressedBgColor;
        this->initStyle();
    }
}

void NavPage::setPressedTextColor(const QColor &pressedTextColor)
{
    if (this->pressedTextColor != pressedTextColor) {
        this->pressedTextColor = pressedTextColor;
        this->initStyle();
    }
}

void NavPage::setCheckedBgColor(const QColor &checkedBgColor)
{
    if (this->checkedBgColor != checkedBgColor) {
        this->checkedBgColor = checkedBgColor;
        this->initStyle();
    }
}

void NavPage::setCheckedTextColor(const QColor &checkedTextColor)
{
    if (this->checkedTextColor != checkedTextColor) {
        this->checkedTextColor = checkedTextColor;
        this->initStyle();
    }
}

void NavPage::setNormalColor(const QColor &bgColor, const QColor &textColor)
{
    this->normalBgColor = bgColor;
    this->normalTextColor = textColor;
    this->initStyle();
}

void NavPage::setDarkColor(const QColor &bgColor, const QColor &textColor)
{
    this->hoverBgColor = bgColor;
    this->pressedBgColor = bgColor;
    this->checkedBgColor = bgColor;
    this->hoverTextColor = textColor;
    this->pressedTextColor = textColor;
    this->checkedTextColor = textColor;
    this->initStyle();
}
