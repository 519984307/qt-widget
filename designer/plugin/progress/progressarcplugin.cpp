#include "progressarc.h"
#include "progressarcplugin.h"

#include <QtPlugin>

ProgressArcPlugin::ProgressArcPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ProgressArcPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressArcPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressArcPlugin::createWidget(QWidget *parent)
{
    return new ProgressArc(parent);
}

QString ProgressArcPlugin::name() const
{
    return QLatin1String("ProgressArc");
}

QString ProgressArcPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressArcPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/progressarc.png"));
}

QString ProgressArcPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressArcPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressArcPlugin::isContainer() const
{
    return false;
}

QString ProgressArcPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressArc\" name=\"progressArc\">\n</widget>\n");
}

QString ProgressArcPlugin::includeFile() const
{
    return QLatin1String("progressarc.h");
}
