#include "shadowcalendar.h"
#include "shadowcalendarplugin.h"

#include <QtPlugin>

ShadowCalendarPlugin::ShadowCalendarPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ShadowCalendarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ShadowCalendarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ShadowCalendarPlugin::createWidget(QWidget *parent)
{
    return new ShadowCalendar(parent);
}

QString ShadowCalendarPlugin::name() const
{
    return QLatin1String("ShadowCalendar");
}

QString ShadowCalendarPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ShadowCalendarPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/shadowcalendar.png"));
}

QString ShadowCalendarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ShadowCalendarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ShadowCalendarPlugin::isContainer() const
{
    return false;
}

QString ShadowCalendarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ShadowCalendar\" name=\"shadowCalendar\">\n</widget>\n");
}

QString ShadowCalendarPlugin::includeFile() const
{
    return QLatin1String("shadowcalendar.h");
}
