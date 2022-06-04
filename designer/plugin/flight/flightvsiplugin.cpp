#include "flightvsi.h"
#include "flightvsiplugin.h"

#include <QtPlugin>

FlightVSIPlugin::FlightVSIPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void FlightVSIPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool FlightVSIPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *FlightVSIPlugin::createWidget(QWidget *parent)
{
    return new FlightVSI(parent);
}

QString FlightVSIPlugin::name() const
{
    return QLatin1String("FlightVSI");
}

QString FlightVSIPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon FlightVSIPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/flightvsi.png"));
}

QString FlightVSIPlugin::toolTip() const
{
    return QLatin1String("");
}

QString FlightVSIPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool FlightVSIPlugin::isContainer() const
{
    return false;
}

QString FlightVSIPlugin::domXml() const
{
    return QLatin1String("<widget class=\"FlightVSI\" name=\"flightVSI\">\n</widget>\n");
}

QString FlightVSIPlugin::includeFile() const
{
    return QLatin1String("flightvsi.h");
}
