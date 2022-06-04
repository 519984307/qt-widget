#include "timeaxis.h"
#include "timeaxisplugin.h"

#include <QtPlugin>

TimeAxisPlugin::TimeAxisPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void TimeAxisPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TimeAxisPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TimeAxisPlugin::createWidget(QWidget *parent)
{
    return new TimeAxis(parent);
}

QString TimeAxisPlugin::name() const
{
    return QLatin1String("TimeAxis");
}

QString TimeAxisPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon TimeAxisPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/timeaxis.png"));
}

QString TimeAxisPlugin::toolTip() const
{
    return QLatin1String("");
}

QString TimeAxisPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool TimeAxisPlugin::isContainer() const
{
    return false;
}

QString TimeAxisPlugin::domXml() const
{
    return QLatin1String("<widget class=\"TimeAxis\" name=\"timeAxis\">\n</widget>\n");
}

QString TimeAxisPlugin::includeFile() const
{
    return QLatin1String("timeaxis.h");
}
