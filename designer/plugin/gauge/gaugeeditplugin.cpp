#include "gaugeedit.h"
#include "gaugeeditplugin.h"

#include <QtPlugin>

GaugeEditPlugin::GaugeEditPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugeEditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeEditPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeEditPlugin::createWidget(QWidget *parent)
{
    return new GaugeEdit(parent);
}

QString GaugeEditPlugin::name() const
{
    return QLatin1String("GaugeEdit");
}

QString GaugeEditPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeEditPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/gaugeedit.png"));
}

QString GaugeEditPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeEditPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeEditPlugin::isContainer() const
{
    return false;
}

QString GaugeEditPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeEdit\" name=\"gaugeEdit\">\n</widget>\n");
}

QString GaugeEditPlugin::includeFile() const
{
    return QLatin1String("gaugeedit.h");
}
