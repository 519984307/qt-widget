#include "navpage.h"
#include "navpageplugin.h"

#include <QtPlugin>

NavPagePlugin::NavPagePlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void NavPagePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NavPagePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NavPagePlugin::createWidget(QWidget *parent)
{
    return new NavPage(parent);
}

QString NavPagePlugin::name() const
{
    return QLatin1String("NavPage");
}

QString NavPagePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon NavPagePlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/navpage.png"));
}

QString NavPagePlugin::toolTip() const
{
    return QLatin1String("");
}

QString NavPagePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool NavPagePlugin::isContainer() const
{
    return false;
}

QString NavPagePlugin::domXml() const
{
    return QLatin1String("<widget class=\"NavPage\" name=\"navPage\">\n</widget>\n");
}

QString NavPagePlugin::includeFile() const
{
    return QLatin1String("navpage.h");
}
