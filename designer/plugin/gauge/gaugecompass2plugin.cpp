#include "gaugecompass2.h"
#include "gaugecompass2plugin.h"

#include <QtPlugin>

GaugeCompass2Plugin::GaugeCompass2Plugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void GaugeCompass2Plugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeCompass2Plugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeCompass2Plugin::createWidget(QWidget *parent)
{
    return new GaugeCompass2(parent);
}

QString GaugeCompass2Plugin::name() const
{
    return QLatin1String("GaugeCompass2");
}

QString GaugeCompass2Plugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeCompass2Plugin::icon() const
{
    return QIcon(QLatin1String(":/icon/gaugecompass2.png"));
}

QString GaugeCompass2Plugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeCompass2Plugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeCompass2Plugin::isContainer() const
{
    return false;
}

QString GaugeCompass2Plugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeCompass2\" name=\"gaugeCompass2\">\n</widget>\n");
}

QString GaugeCompass2Plugin::includeFile() const
{
    return QLatin1String("gaugecompass2.h");
}
