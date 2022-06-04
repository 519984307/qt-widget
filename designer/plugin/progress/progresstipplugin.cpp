#include "progresstip.h"
#include "progresstipplugin.h"

#include <QtPlugin>

ProgressTipPlugin::ProgressTipPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ProgressTipPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressTipPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressTipPlugin::createWidget(QWidget *parent)
{
    return new ProgressTip(parent);
}

QString ProgressTipPlugin::name() const
{
    return QLatin1String("ProgressTip");
}

QString ProgressTipPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressTipPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/progresstip.png"));
}

QString ProgressTipPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressTipPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressTipPlugin::isContainer() const
{
    return false;
}

QString ProgressTipPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressTip\" name=\"progressTip\">\n</widget>\n");
}

QString ProgressTipPlugin::includeFile() const
{
    return QLatin1String("progresstip.h");
}
