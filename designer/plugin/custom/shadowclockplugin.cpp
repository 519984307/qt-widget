#include "shadowclock.h"
#include "shadowclockplugin.h"

#include <QtPlugin>

ShadowClockPlugin::ShadowClockPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ShadowClockPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ShadowClockPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ShadowClockPlugin::createWidget(QWidget *parent)
{
    return new ShadowClock(parent);
}

QString ShadowClockPlugin::name() const
{
    return QLatin1String("ShadowClock");
}

QString ShadowClockPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ShadowClockPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/shadowclock.png"));
}

QString ShadowClockPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ShadowClockPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ShadowClockPlugin::isContainer() const
{
    return false;
}

QString ShadowClockPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ShadowClock\" name=\"shadowClock\">\n</widget>\n");
}

QString ShadowClockPlugin::includeFile() const
{
    return QLatin1String("shadowclock.h");
}
