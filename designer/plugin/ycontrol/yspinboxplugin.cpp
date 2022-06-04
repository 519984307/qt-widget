#include "yspinbox.h"
#include "yspinboxplugin.h"

#include <QtPlugin>

YSpinBoxPlugin::YSpinBoxPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void YSpinBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool YSpinBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *YSpinBoxPlugin::createWidget(QWidget *parent)
{
    return new YSpinBox(parent);
}

QString YSpinBoxPlugin::name() const
{
    return QLatin1String("YSpinBox");
}

QString YSpinBoxPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon YSpinBoxPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/yspinbox.png"));
}

QString YSpinBoxPlugin::toolTip() const
{
    return QLatin1String("");
}

QString YSpinBoxPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool YSpinBoxPlugin::isContainer() const
{
    return false;
}

QString YSpinBoxPlugin::domXml() const
{
    return QLatin1String("<widget class=\"YSpinBox\" name=\"ySpinBox\">\n</widget>\n");
}

QString YSpinBoxPlugin::includeFile() const
{
    return QLatin1String("yspinbox.h");
}
