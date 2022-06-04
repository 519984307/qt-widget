#include "progressshadow.h"
#include "progressshadowplugin.h"

#include <QtPlugin>

ProgressShadowPlugin::ProgressShadowPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ProgressShadowPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressShadowPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressShadowPlugin::createWidget(QWidget *parent)
{
    return new ProgressShadow(parent);
}

QString ProgressShadowPlugin::name() const
{
    return QLatin1String("ProgressShadow");
}

QString ProgressShadowPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressShadowPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/progressshadow.png"));
}

QString ProgressShadowPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressShadowPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressShadowPlugin::isContainer() const
{
    return false;
}

QString ProgressShadowPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressShadow\" name=\"progressShadow\">\n</widget>\n");
}

QString ProgressShadowPlugin::includeFile() const
{
    return QLatin1String("progressshadow.h");
}
