#include "shadowwidget.h"
#include "shadowwidgetplugin.h"

#include <QtPlugin>

ShadowWidgetPlugin::ShadowWidgetPlugin(QObject *parent) : QObject(parent)
{
	m_initialized = false;
}

void ShadowWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
	if (m_initialized)
		return;

	// Add extension registrations, etc. here

	m_initialized = true;
}

bool ShadowWidgetPlugin::isInitialized() const
{
	return m_initialized;
}

QWidget *ShadowWidgetPlugin::createWidget(QWidget *parent)
{
	return new ShadowWidget(parent);
}

QString ShadowWidgetPlugin::name() const
{
	return QLatin1String("ShadowWidget");
}

QString ShadowWidgetPlugin::group() const
{
	return QLatin1String("Quc Widgets");
}

QIcon ShadowWidgetPlugin::icon() const
{
	return QIcon(QLatin1String(":/icon/shadowwidget.png"));
}

QString ShadowWidgetPlugin::toolTip() const
{
	return QLatin1String("");
}

QString ShadowWidgetPlugin::whatsThis() const
{
	return QLatin1String("");
}

bool ShadowWidgetPlugin::isContainer() const
{
    return true;
}

QString ShadowWidgetPlugin::domXml() const
{
	return QLatin1String("<widget class=\"ShadowWidget\" name=\"shadowWidget\">\n</widget>\n");
}

QString ShadowWidgetPlugin::includeFile() const
{
	return QLatin1String("shadowwidget.h");
}
