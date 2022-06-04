#include "ydoublespinbox.h"
#include "ydoublespinboxplugin.h"

#include <QtPlugin>

YDoubleSpinBoxPlugin::YDoubleSpinBoxPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void YDoubleSpinBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool YDoubleSpinBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *YDoubleSpinBoxPlugin::createWidget(QWidget *parent)
{
    return new YDoubleSpinBox(parent);
}

QString YDoubleSpinBoxPlugin::name() const
{
    return QLatin1String("YDoubleSpinBox");
}

QString YDoubleSpinBoxPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon YDoubleSpinBoxPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/ydoublespinbox.png"));
}

QString YDoubleSpinBoxPlugin::toolTip() const
{
    return QLatin1String("");
}

QString YDoubleSpinBoxPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool YDoubleSpinBoxPlugin::isContainer() const
{
    return false;
}

QString YDoubleSpinBoxPlugin::domXml() const
{
    return QLatin1String("<widget class=\"YDoubleSpinBox\" name=\"yDoubleSpinBox\">\n</widget>\n");
}

QString YDoubleSpinBoxPlugin::includeFile() const
{
    return QLatin1String("ydoublespinbox.h");
}
