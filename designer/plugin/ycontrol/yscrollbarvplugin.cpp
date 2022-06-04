#include "yscrollbarv.h"
#include "yscrollbarvplugin.h"

#include <QtPlugin>

YScrollBarVPlugin::YScrollBarVPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void YScrollBarVPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool YScrollBarVPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *YScrollBarVPlugin::createWidget(QWidget *parent)
{
    return new YScrollBarV(parent);
}

QString YScrollBarVPlugin::name() const
{
    return QLatin1String("YScrollBarV");
}

QString YScrollBarVPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon YScrollBarVPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/yscrollbarv.png"));
}

QString YScrollBarVPlugin::toolTip() const
{
    return QLatin1String("");
}

QString YScrollBarVPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool YScrollBarVPlugin::isContainer() const
{
    return false;
}

QString YScrollBarVPlugin::domXml() const
{
    return QLatin1String("<widget class=\"YScrollBarV\" name=\"yScrollBarV\">\n</widget>\n");
}

QString YScrollBarVPlugin::includeFile() const
{
    return QLatin1String("yscrollbarv.h");
}
