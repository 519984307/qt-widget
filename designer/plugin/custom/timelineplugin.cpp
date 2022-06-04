#include "timeline.h"
#include "timelineplugin.h"

#include <QtPlugin>

TimeLinePlugin::TimeLinePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void TimeLinePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TimeLinePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TimeLinePlugin::createWidget(QWidget *parent)
{
    return new TimeLine(parent);
}

QString TimeLinePlugin::name() const
{
    return QLatin1String("TimeLine");
}

QString TimeLinePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon TimeLinePlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/timeline.png"));
}

QString TimeLinePlugin::toolTip() const
{
    return QLatin1String("");
}

QString TimeLinePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool TimeLinePlugin::isContainer() const
{
    return false;
}

QString TimeLinePlugin::domXml() const
{
    return QLatin1String("<widget class=\"TimeLine\" name=\"timeLine\">\n</widget>\n");
}

QString TimeLinePlugin::includeFile() const
{
    return QLatin1String("timeline.h");
}
