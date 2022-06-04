#include "yscrollbarh.h"
#include "yscrollbarhplugin.h"

#include <QtPlugin>

YScrollBarHPlugin::YScrollBarHPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void YScrollBarHPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool YScrollBarHPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *YScrollBarHPlugin::createWidget(QWidget *parent)
{
    return new YScrollBarH(parent);
}

QString YScrollBarHPlugin::name() const
{
    return QLatin1String("YScrollBarH");
}

QString YScrollBarHPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon YScrollBarHPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/yscrollbarh.png"));
}

QString YScrollBarHPlugin::toolTip() const
{
    return QLatin1String("");
}

QString YScrollBarHPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool YScrollBarHPlugin::isContainer() const
{
    return false;
}

QString YScrollBarHPlugin::domXml() const
{
    return QLatin1String("<widget class=\"YScrollBarH\" name=\"yScrollBarH\">\n</widget>\n");
}

QString YScrollBarHPlugin::includeFile() const
{
    return QLatin1String("yscrollbarh.h");
}
