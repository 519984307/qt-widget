#include "wavewater.h"
#include "wavewaterplugin.h"

#include <QtPlugin>

WaveWaterPlugin::WaveWaterPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void WaveWaterPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool WaveWaterPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *WaveWaterPlugin::createWidget(QWidget *parent)
{
    return new WaveWater(parent);
}

QString WaveWaterPlugin::name() const
{
    return QLatin1String("WaveWater");
}

QString WaveWaterPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon WaveWaterPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/wavewater.png"));
}

QString WaveWaterPlugin::toolTip() const
{
    return QLatin1String("");
}

QString WaveWaterPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool WaveWaterPlugin::isContainer() const
{
    return false;
}

QString WaveWaterPlugin::domXml() const
{
    return QLatin1String("<widget class=\"WaveWater\" name=\"waveWater\">\n</widget>\n");
}

QString WaveWaterPlugin::includeFile() const
{
    return QLatin1String("wavewater.h");
}
