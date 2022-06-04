#include "ylistwidget.h"
#include "ylistwidgetplugin.h"

#include <QtPlugin>

YListWidgetPlugin::YListWidgetPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void YListWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool YListWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *YListWidgetPlugin::createWidget(QWidget *parent)
{
    return new YListWidget(parent);
}

QString YListWidgetPlugin::name() const
{
    return QLatin1String("YListWidget");
}

QString YListWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon YListWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/ylistwidget.png"));
}

QString YListWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString YListWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool YListWidgetPlugin::isContainer() const
{
    return false;
}

QString YListWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"YListWidget\" name=\"yListWidget\">\n</widget>\n");
}

QString YListWidgetPlugin::includeFile() const
{
    return QLatin1String("ylistwidget.h");
}
