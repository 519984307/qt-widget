#include "xstackwidget.h"
#include "xstackwidgetplugin.h"

#include <QtPlugin>

XStackWidgetPlugin::XStackWidgetPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void XStackWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool XStackWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *XStackWidgetPlugin::createWidget(QWidget *parent)
{
    return new XStackWidget(parent);
}

QString XStackWidgetPlugin::name() const
{
    return QLatin1String("XStackWidget");
}

QString XStackWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon XStackWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/xstackwidget.png"));
}

QString XStackWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString XStackWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool XStackWidgetPlugin::isContainer() const
{
    return false;
}

QString XStackWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"XStackWidget\" name=\"xStackWidget\">\n</widget>\n");
}

QString XStackWidgetPlugin::includeFile() const
{
    return QLatin1String("xstackwidget.h");
}
