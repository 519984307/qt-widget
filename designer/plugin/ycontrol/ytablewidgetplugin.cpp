#include "ytablewidget.h"
#include "ytablewidgetplugin.h"

#include <QtPlugin>

YTableWidgetPlugin::YTableWidgetPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void YTableWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool YTableWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *YTableWidgetPlugin::createWidget(QWidget *parent)
{
    return new YTableWidget(parent);
}

QString YTableWidgetPlugin::name() const
{
    return QLatin1String("YTableWidget");
}

QString YTableWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon YTableWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/ytablewidget.png"));
}

QString YTableWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString YTableWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool YTableWidgetPlugin::isContainer() const
{
    return false;
}

QString YTableWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"YTableWidget\" name=\"yTableWidget\">\n</widget>\n");
}

QString YTableWidgetPlugin::includeFile() const
{
    return QLatin1String("ytablewidget.h");
}
