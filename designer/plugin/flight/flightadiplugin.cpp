#include "flightadi.h"
#include "flightadiplugin.h"

#include <QtPlugin>

FlightADIPlugin::FlightADIPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void FlightADIPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool FlightADIPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *FlightADIPlugin::createWidget(QWidget *parent)
{
    return new FlightADI(parent);
}

QString FlightADIPlugin::name() const
{
    return QLatin1String("FlightADI");
}

QString FlightADIPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon FlightADIPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/flightadi.png"));
}

QString FlightADIPlugin::toolTip() const
{
    return QLatin1String("");
}

QString FlightADIPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool FlightADIPlugin::isContainer() const
{
    return false;
}

QString FlightADIPlugin::domXml() const
{
    return QLatin1String("<widget class=\"FlightADI\" name=\"flightADI\">\n</widget>\n");
}

QString FlightADIPlugin::includeFile() const
{
    return QLatin1String("flightadi.h");
}
