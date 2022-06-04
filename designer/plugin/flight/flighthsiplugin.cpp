#include "flighthsi.h"
#include "flighthsiplugin.h"

#include <QtPlugin>

FlightHSIPlugin::FlightHSIPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void FlightHSIPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool FlightHSIPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *FlightHSIPlugin::createWidget(QWidget *parent)
{
    return new FlightHSI(parent);
}

QString FlightHSIPlugin::name() const
{
    return QLatin1String("FlightHSI");
}

QString FlightHSIPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon FlightHSIPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/flighthsi.png"));
}

QString FlightHSIPlugin::toolTip() const
{
    return QLatin1String("");
}

QString FlightHSIPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool FlightHSIPlugin::isContainer() const
{
    return false;
}

QString FlightHSIPlugin::domXml() const
{
    return QLatin1String("<widget class=\"FlightHSI\" name=\"flightHSI\">\n</widget>\n");
}

QString FlightHSIPlugin::includeFile() const
{
    return QLatin1String("flighthsi.h");
}
