#include "scantantan.h"
#include "scantantanplugin.h"

#include <QtPlugin>

ScanTanTanPlugin::ScanTanTanPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void ScanTanTanPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ScanTanTanPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ScanTanTanPlugin::createWidget(QWidget *parent)
{
    return new ScanTanTan(parent);
}

QString ScanTanTanPlugin::name() const
{
    return QLatin1String("ScanTanTan");
}

QString ScanTanTanPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ScanTanTanPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/scantantan.png"));
}

QString ScanTanTanPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ScanTanTanPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ScanTanTanPlugin::isContainer() const
{
    return false;
}

QString ScanTanTanPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ScanTanTan\" name=\"scanTanTan\">\n</widget>\n");
}

QString ScanTanTanPlugin::includeFile() const
{
    return QLatin1String("scantantan.h");
}
