#include "xcombobox.h"
#include "xcomboboxplugin.h"

#include <QtPlugin>

XComboBoxPlugin::XComboBoxPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void XComboBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool XComboBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *XComboBoxPlugin::createWidget(QWidget *parent)
{
    return new XComboBox(parent);
}

QString XComboBoxPlugin::name() const
{
    return QLatin1String("XComboBox");
}

QString XComboBoxPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon XComboBoxPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/xcombobox.png"));
}

QString XComboBoxPlugin::toolTip() const
{
    return QLatin1String("");
}

QString XComboBoxPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool XComboBoxPlugin::isContainer() const
{
    return false;
}

QString XComboBoxPlugin::domXml() const
{
    return QLatin1String("<widget class=\"XComboBox\" name=\"xcomboBox\">\n</widget>\n");
}

QString XComboBoxPlugin::includeFile() const
{
    return QLatin1String("xcombobox.h");
}

