#include "navbuttongroup.h"
#include "navbuttongroupplugin.h"

#include <QtPlugin>

NavButtonGroupPlugin::NavButtonGroupPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void NavButtonGroupPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NavButtonGroupPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NavButtonGroupPlugin::createWidget(QWidget *parent)
{
    return new NavButtonGroup(parent);
}

QString NavButtonGroupPlugin::name() const
{
    return QLatin1String("NavButtonGroup");
}

QString NavButtonGroupPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon NavButtonGroupPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/navbuttongroup.png"));
}

QString NavButtonGroupPlugin::toolTip() const
{
    return QLatin1String("");
}

QString NavButtonGroupPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool NavButtonGroupPlugin::isContainer() const
{
    return false;
}

QString NavButtonGroupPlugin::domXml() const
{
    return QLatin1String("<widget class=\"NavButtonGroup\" name=\"navButtonGroup\">\n</widget>\n");
}

QString NavButtonGroupPlugin::includeFile() const
{
    return QLatin1String("navbuttongroup.h");
}
