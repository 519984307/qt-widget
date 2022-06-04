#include "flightasi.h"
#include "flightasiplugin.h"

#include <QtPlugin>

FlightASIPlugin::FlightASIPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void FlightASIPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool FlightASIPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *FlightASIPlugin::createWidget(QWidget *parent)
{
    return new FlightASI(parent);
}

QString FlightASIPlugin::name() const
{
    return QLatin1String("FlightASI");
}

QString FlightASIPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon FlightASIPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/flightasi.png"));
}

QString FlightASIPlugin::toolTip() const
{
    return QLatin1String("");
}

QString FlightASIPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool FlightASIPlugin::isContainer() const
{
    return false;
}

QString FlightASIPlugin::domXml() const
{
    return QLatin1String("<widget class=\"FlightASI\" name=\"flightASI\">\n</widget>\n");
}

QString FlightASIPlugin::includeFile() const
{
    return QLatin1String("flightasi.h");
}
