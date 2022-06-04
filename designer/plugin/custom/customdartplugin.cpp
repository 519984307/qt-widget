#include "customdart.h"
#include "customdartplugin.h"

#include <QtPlugin>

CustomDartPlugin::CustomDartPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void CustomDartPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CustomDartPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CustomDartPlugin::createWidget(QWidget *parent)
{
    return new CustomDart(parent);
}

QString CustomDartPlugin::name() const
{
    return QLatin1String("CustomDart");
}

QString CustomDartPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon CustomDartPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/customdart.png"));
}

QString CustomDartPlugin::toolTip() const
{
    return QLatin1String("");
}

QString CustomDartPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CustomDartPlugin::isContainer() const
{
    return false;
}

QString CustomDartPlugin::domXml() const
{
    return QLatin1String("<widget class=\"CustomDart\" name=\"customDart\">\n</widget>\n");
}

QString CustomDartPlugin::includeFile() const
{
    return QLatin1String("customdart.h");
}
