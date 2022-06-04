#pragma execution_character_set("utf-8")

#include "frmnavbar.h"
#include "frmnavbarform.h"
#include "qtabwidget.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(13);
    a.setFont(font);

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif

    QTabWidget w;
    w.addTab(new frmNavBar, "滑动导航条");
    w.addTab(new frmNavBarForm, "滑动导航界面");
    w.setWindowTitle("滑动导航示例 (QQ: 517216493 WX: feiyangqingyun)");
    w.resize(500, 300);
    w.show();

    return a.exec();
}
