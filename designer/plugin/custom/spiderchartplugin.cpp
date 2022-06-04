#include "spiderchart.h"
#include "spiderchartplugin.h"

#include <QtPlugin>

SpiderChartPlugin::SpiderChartPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void SpiderChartPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool SpiderChartPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SpiderChartPlugin::createWidget(QWidget *parent)
{
    return new SpiderChart(parent);
}

QString SpiderChartPlugin::name() const
{
    return QLatin1String("SpiderChart");
}

QString SpiderChartPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon SpiderChartPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/spiderchart.png"));
}

QString SpiderChartPlugin::toolTip() const
{
    return QLatin1String("");
}

QString SpiderChartPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool SpiderChartPlugin::isContainer() const
{
    return false;
}

QString SpiderChartPlugin::domXml() const
{
    return QLatin1String("<widget class=\"SpiderChart\" name=\"spiderChart\">\n</widget>\n");
}

QString SpiderChartPlugin::includeFile() const
{
    return QLatin1String("spiderchart.h");
}
