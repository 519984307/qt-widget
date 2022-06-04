#include "frmexamplesfull.h"
#include "frmexamplessimple.h"
#include "head.h"

void setFont()
{
    QString fontFile = ":/font/DroidSansFallback.ttf";
    QString fontName = "Microsoft Yahei";
    int fontSize = 13;

    QFont font;
    font.setFamily(fontName);
    font.setPixelSize(fontSize);

    //如果存在字体文件则设备字体文件中的字体
    //安卓版本和网页版本需要字体文件一起打包单独设置字体
    if (QFile(fontFile).exists()) {
        QFontDatabase fontDb;
        int fontId = fontDb.addApplicationFont(fontFile);
        if (fontId != -1) {
            QStringList fontNames = fontDb.applicationFontFamilies(fontId);
            if (fontNames.count() > 0) {
                font.setFamily(fontNames.at(0));
                font.setPixelSize(fontSize);
            }
        }
    }

    qApp->setFont(font);
}

void setCode()
{
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
}

void setTranslator(const QString &qmFile)
{
    QTranslator *translator = new QTranslator(qApp);
    translator->load(qmFile);
    qApp->installTranslator(translator);
}

void initStyle()
{
#ifdef Q_OS_ANDROID
    //复选框单选框滑块等指示器大小
    QStringList list;
    int rbtnWidth = 20;
    int ckWidth = 18;
    list << QString("QRadioButton::indicator{width:%1px;height:%1px;}").arg(rbtnWidth);
    list << QString("QCheckBox::indicator,QGroupBox::indicator,QTreeWidget::indicator,QListWidget::indicator{width:%1px;height:%1px;}").arg(ckWidth);

    QString normalColor = "#E8EDF2";
    QString grooveColor = "#1ABC9C";
    QString handleColor = "#1ABC9C";
    int sliderHeight = 15;
    int sliderRadius = sliderHeight / 2;
    int handleWidth = (sliderHeight * 3) / 2 + (sliderHeight / 5);
    int handleRadius = handleWidth / 2;
    int handleOffset = handleRadius / 2;

    list << QString("QSlider::horizontal{min-height:%1px;}").arg(sliderHeight * 2);
    list << QString("QSlider::groove:horizontal{background:%1;height:%2px;border-radius:%3px;}")
            .arg(normalColor).arg(sliderHeight).arg(sliderRadius);
    list << QString("QSlider::add-page:horizontal{background:%1;height:%2px;border-radius:%3px;}")
            .arg(normalColor).arg(sliderHeight).arg(sliderRadius);
    list << QString("QSlider::sub-page:horizontal{background:%1;height:%2px;border-radius:%3px;}")
            .arg(grooveColor).arg(sliderHeight).arg(sliderRadius);
    list << QString("QSlider::handle:horizontal{width:%2px;margin-top:-%3px;margin-bottom:-%3px;border-radius:%4px;"
                    "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 %1);}")
            .arg(handleColor).arg(handleWidth).arg(handleOffset).arg(handleRadius);

    //偏移一个像素
    handleWidth = handleWidth + 1;
    list << QString("QSlider::vertical{min-width:%1px;}").arg(sliderHeight * 2);
    list << QString("QSlider::groove:vertical{background:%1;width:%2px;border-radius:%3px;}")
            .arg(normalColor).arg(sliderHeight).arg(sliderRadius);
    list << QString("QSlider::add-page:vertical{background:%1;width:%2px;border-radius:%3px;}")
            .arg(grooveColor).arg(sliderHeight).arg(sliderRadius);
    list << QString("QSlider::sub-page:vertical{background:%1;width:%2px;border-radius:%3px;}")
            .arg(normalColor).arg(sliderHeight).arg(sliderRadius);
    list << QString("QSlider::handle:vertical{height:%2px;margin-left:-%3px;margin-right:-%3px;border-radius:%4px;"
                    "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 %1);}")
            .arg(handleColor).arg(handleWidth).arg(handleOffset).arg(handleRadius);

    qApp->setStyleSheet(list.join(""));
#else
    //加了系统样式居然会导致左侧树状导航列表移除效果不明显
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    qApp->setStyle(QStyleFactory::create("Fusion"));
#else
    qApp->setStyle(QStyleFactory::create("Cleanlooks"));
#endif
    QPalette palette;
    palette.setBrush(QPalette::Window, QColor("#F0F0F0"));
    qApp->setPalette(palette);
#endif
}

void initOther()
{
    //初始化随机数种子
    QTime t = QTime::currentTime();
    srand(t.msec() + t.second() * 1000);
}

int main(int argc, char *argv[])
{
    //设置不应用操作系统设置比如字体
    QApplication::setDesktopSettingsAware(false);

#ifdef Q_OS_ANDROID
#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#else
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    QApplication::setAttribute(Qt::AA_Use96Dpi);
#endif
#endif

#if (QT_VERSION >= QT_VERSION_CHECK(5,14,0))
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
#endif

    QApplication a(argc, argv);
    setFont();
    setCode();
    setTranslator(":/qm/qt_zh_CN.qm");
    setTranslator(":/qm/widgets.qm");
    initStyle();
    initOther();

#ifdef examples_full
    frmExamplesFull w;
#else
    frmExamplesSimple w;
#endif
    w.resize(1050, 650);
    w.show();

    return a.exec();
}
