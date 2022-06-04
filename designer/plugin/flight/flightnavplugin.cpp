#include "flightnav.h"
#include "flightnavplugin.h"

#include <QtPlugin>

FlightNAVPlugin::FlightNAVPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void FlightNAVPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool FlightNAVPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *FlightNAVPlugin::createWidget(QWidget *parent)
{
    return new FlightNAV(parent);
}

QString FlightNAVPlugin::name() const
{
    return QLatin1String("FlightNAV");
}

QString FlightNAVPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon FlightNAVPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/flightnav.png"));
}

QString FlightNAVPlugin::toolTip() const
{
    return QLatin1String("");
}

QString FlightNAVPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool FlightNAVPlugin::isContainer() const
{
    return false;
}

QString FlightNAVPlugin::domXml() const
{
    return QLatin1String("<widget class=\"FlightNAV\" name=\"flightNAV\">\n</widget>\n");
}

QString FlightNAVPlugin::includeFile() const
{
    return QLatin1String("flightnav.h");
}
