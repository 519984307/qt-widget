#include "xtablewidget.h"
#include "xtablewidgetplugin.h"

#include <QtPlugin>

XTableWidgetPlugin::XTableWidgetPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void XTableWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool XTableWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *XTableWidgetPlugin::createWidget(QWidget *parent)
{
    return new XTableWidget(parent);
}

QString XTableWidgetPlugin::name() const
{
    return QLatin1String("XTableWidget");
}

QString XTableWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon XTableWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/xtablewidget.png"));
}

QString XTableWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString XTableWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool XTableWidgetPlugin::isContainer() const
{
    return false;
}

QString XTableWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"XTableWidget\" name=\"xTableWidget\">\n</widget>\n");
}

QString XTableWidgetPlugin::includeFile() const
{
    return QLatin1String("xtablewidget.h");
}
