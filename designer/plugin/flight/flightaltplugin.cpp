#include "flightalt.h"
#include "flightaltplugin.h"

#include <QtPlugin>

FlightALTPlugin::FlightALTPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void FlightALTPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool FlightALTPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *FlightALTPlugin::createWidget(QWidget *parent)
{
    return new FlightALT(parent);
}

QString FlightALTPlugin::name() const
{
    return QLatin1String("FlightALT");
}

QString FlightALTPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon FlightALTPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/flightalt.png"));
}

QString FlightALTPlugin::toolTip() const
{
    return QLatin1String("");
}

QString FlightALTPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool FlightALTPlugin::isContainer() const
{
    return false;
}

QString FlightALTPlugin::domXml() const
{
    return QLatin1String("<widget class=\"FlightALT\" name=\"flightALT\">\n</widget>\n");
}

QString FlightALTPlugin::includeFile() const
{
    return QLatin1String("flightalt.h");
}
