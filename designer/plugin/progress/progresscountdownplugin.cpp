#include "progresscountdown.h"
#include "progresscountdownplugin.h"

#include <QtPlugin>

ProgressCountDownPlugin::ProgressCountDownPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ProgressCountDownPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressCountDownPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressCountDownPlugin::createWidget(QWidget *parent)
{
    return new ProgressCountDown(parent);
}

QString ProgressCountDownPlugin::name() const
{
    return QLatin1String("ProgressCountDown");
}

QString ProgressCountDownPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressCountDownPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/progresscountdown.png"));
}

QString ProgressCountDownPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressCountDownPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressCountDownPlugin::isContainer() const
{
    return false;
}

QString ProgressCountDownPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressCountDown\" name=\"progressCountDown\">\n</widget>\n");
}

QString ProgressCountDownPlugin::includeFile() const
{
    return QLatin1String("progresscountdown.h");
}
