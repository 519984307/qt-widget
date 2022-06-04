#include "devicebutton.h"
#include "devicebuttonplugin.h"

#include <QtPlugin>

DeviceButtonPlugin::DeviceButtonPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void DeviceButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool DeviceButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *DeviceButtonPlugin::createWidget(QWidget *parent)
{
    return new DeviceButton(parent);
}

QString DeviceButtonPlugin::name() const
{
    return QLatin1String("DeviceButton");
}

QString DeviceButtonPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon DeviceButtonPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/devicebutton.png"));
}

QString DeviceButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString DeviceButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool DeviceButtonPlugin::isContainer() const
{
    return false;
}

QString DeviceButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"DeviceButton\" name=\"deviceButton\">\n</widget>\n");
}

QString DeviceButtonPlugin::includeFile() const
{
    return QLatin1String("devicebutton.h");
}
