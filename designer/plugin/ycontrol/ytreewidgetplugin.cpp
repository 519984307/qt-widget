#include "ytreewidget.h"
#include "ytreewidgetplugin.h"

#include <QtPlugin>

YTreeWidgetPlugin::YTreeWidgetPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void YTreeWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool YTreeWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *YTreeWidgetPlugin::createWidget(QWidget *parent)
{
    return new YTreeWidget(parent);
}

QString YTreeWidgetPlugin::name() const
{
    return QLatin1String("YTreeWidget");
}

QString YTreeWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon YTreeWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/ytreewidget.png"));
}

QString YTreeWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString YTreeWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool YTreeWidgetPlugin::isContainer() const
{
    return false;
}

QString YTreeWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"YTreeWidget\" name=\"yTreeWidget\">\n</widget>\n");
}

QString YTreeWidgetPlugin::includeFile() const
{
    return QLatin1String("ytreewidget.h");
}
