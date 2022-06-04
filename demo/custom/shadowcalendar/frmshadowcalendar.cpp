#pragma execution_character_set("utf-8")

#include "frmshadowcalendar.h"
#include "ui_frmshadowcalendar.h"
#include "qfontdatabase.h"
#include "qdebug.h"

frmShadowCalendar::frmShadowCalendar(QWidget *parent) : QWidget(parent), ui(new Ui::frmShadowCalendar)
{
    ui->setupUi(this);
    this->initForm();
}

frmShadowCalendar::~frmShadowCalendar()
{
}

void frmShadowCalendar::initForm()
{
    //判断图形字体是否存在,不存在则加入
    QFontDatabase fontDb;
    QFont iconFont;
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

    //设置图形字体
    iconFont.setPixelSize(30);
    ui->btnUp->setFont(iconFont);
    ui->btnDown->setFont(iconFont);
    ui->btnUp->setText((QChar)0xf106);
    ui->btnDown->setText((QChar)0xf107);

    //设置样式表
    QStringList qss;
    //qss << "#frmShadowCalendar{background:#212425;}";
    qss << "#line{border:1px solid #888888;}";
    qss << "#labInfo{font:18px;color:#43C1FB;}";
    qss << "#btnUp,#btnDown{color:#FFFFFF;background:rgba(0,0,0,0);padding:0px;}";
    qss << "#btnUp:hover,#btnDown:hover{color:#43C1FB;}";
    this->setStyleSheet(qss.join(""));

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QColor("#212425"));
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    currentDate = QDateTime::currentDateTime();
    updateInfo();
}

void frmShadowCalendar::updateInfo()
{
    ui->labInfo->setText(currentDate.toString("yyyy年MM月dd日  ddd"));
}

void frmShadowCalendar::on_btnUp_clicked()
{
    currentDate = currentDate.addMonths(-1);
    ui->shadowCalendar->updateCalendar(currentDate.date());
    updateInfo();
}

void frmShadowCalendar::on_btnDown_clicked()
{
    currentDate = currentDate.addMonths(1);
    ui->shadowCalendar->updateCalendar(currentDate.date());
    updateInfo();
}
