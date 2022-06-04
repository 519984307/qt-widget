#include "flightpfd.h"
#include "flightpfdplugin.h"

#include <QtPlugin>

FlightPFDPlugin::FlightPFDPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void FlightPFDPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool FlightPFDPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *FlightPFDPlugin::createWidget(QWidget *parent)
{
    return new FlightPFD(parent);
}

QString FlightPFDPlugin::name() const
{
    return QLatin1String("FlightPFD");
}

QString FlightPFDPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon FlightPFDPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/flightpfd.png"));
}

QString FlightPFDPlugin::toolTip() const
{
    return QLatin1String("");
}

QString FlightPFDPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool FlightPFDPlugin::isContainer() const
{
    return false;
}

QString FlightPFDPlugin::domXml() const
{
    return QLatin1String("<widget class=\"FlightPFD\" name=\"flightPFD\">\n</widget>\n");
}

QString FlightPFDPlugin::includeFile() const
{
    return QLatin1String("flightpfd.h");
}
