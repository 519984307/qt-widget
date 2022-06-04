#include "ycombobox.h"
#include "ycomboboxplugin.h"

#include <QtPlugin>

YComboBoxPlugin::YComboBoxPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void YComboBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool YComboBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *YComboBoxPlugin::createWidget(QWidget *parent)
{
    return new YComboBox(parent);
}

QString YComboBoxPlugin::name() const
{
    return QLatin1String("YComboBox");
}

QString YComboBoxPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon YComboBoxPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/ycombobox.png"));
}

QString YComboBoxPlugin::toolTip() const
{
    return QLatin1String("");
}

QString YComboBoxPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool YComboBoxPlugin::isContainer() const
{
    return false;
}

QString YComboBoxPlugin::domXml() const
{
    return QLatin1String("<widget class=\"YComboBox\" name=\"yComboBox\">\n</widget>\n");
}

QString YComboBoxPlugin::includeFile() const
{
    return QLatin1String("ycombobox.h");
}
