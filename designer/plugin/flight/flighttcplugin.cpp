#include "flighttc.h"
#include "flighttcplugin.h"

#include <QtPlugin>

FlightTCPlugin::FlightTCPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void FlightTCPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool FlightTCPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *FlightTCPlugin::createWidget(QWidget *parent)
{
    return new FlightTC(parent);
}

QString FlightTCPlugin::name() const
{
    return QLatin1String("FlightTC");
}

QString FlightTCPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon FlightTCPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/flighttc.png"));
}

QString FlightTCPlugin::toolTip() const
{
    return QLatin1String("");
}

QString FlightTCPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool FlightTCPlugin::isContainer() const
{
    return false;
}

QString FlightTCPlugin::domXml() const
{
    return QLatin1String("<widget class=\"FlightTC\" name=\"flightTC\">\n</widget>\n");
}

QString FlightTCPlugin::includeFile() const
{
    return QLatin1String("flighttc.h");
}
