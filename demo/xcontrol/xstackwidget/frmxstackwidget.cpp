#pragma execution_character_set("utf-8")

#include "frmxstackwidget.h"
#include "ui_frmxstackwidget.h"
#include "qbuttongroup.h"
#include "qlabel.h"

frmXStackWidget::frmXStackWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmXStackWidget)
{
    ui->setupUi(this);
    this->initForm();
}

frmXStackWidget::~frmXStackWidget()
{
    delete ui;
}

void frmXStackWidget::initForm()
{
    QList<QPushButton *> btnlst;
    btnlst << ui->pushButton_1;
    btnlst << ui->pushButton_2;
    btnlst << ui->pushButton_3;
    btnlst << ui->pushButton_4;
    btnlst << ui->pushButton_5;

    QButtonGroup *btnGroup = new QButtonGroup(this);
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    connect(btnGroup, SIGNAL(idClicked(int)), ui->xstackWidget, SLOT(setCurrentIndex(int)));
#else
    connect(btnGroup, SIGNAL(buttonClicked(int)), ui->xstackWidget, SLOT(setCurrentIndex(int)));
#endif

    QList<QString> colorlst;
    colorlst << "#1abc9c";
    colorlst << "#2ecc71";
    colorlst << "#3498db";
    colorlst << "#9b59b6";
    colorlst << "#e74c3c";

    //用label作为演示窗体搞个不同的背景颜色
    for (int i = 0; i < colorlst.count(); i++) {
        QLabel *label = new QLabel(ui->xstackWidget);
        label->setStyleSheet(QString("background-color:%1;color:#ffffff;").arg(colorlst.at(i)));
        label->setText(QString::number(i + 1));
        label->setAlignment(Qt::AlignCenter);
        int index = ui->xstackWidget->addWidget(label);
        btnGroup->addButton(btnlst.at(i), index);
    }
}
