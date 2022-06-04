#include "magicpenguin.h"
#include "magicpenguinplugin.h"

#include <QtPlugin>

MagicPenguinPlugin::MagicPenguinPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void MagicPenguinPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MagicPenguinPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MagicPenguinPlugin::createWidget(QWidget *parent)
{
    return new MagicPenguin(parent);
}

QString MagicPenguinPlugin::name() const
{
    return QLatin1String("MagicPenguin");
}

QString MagicPenguinPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon MagicPenguinPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/magicpenguin.png"));
}

QString MagicPenguinPlugin::toolTip() const
{
    return QLatin1String("");
}

QString MagicPenguinPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool MagicPenguinPlugin::isContainer() const
{
    return false;
}

QString MagicPenguinPlugin::domXml() const
{
    return QLatin1String("<widget class=\"MagicPenguin\" name=\"magicPenguin\">\n</widget>\n");
}

QString MagicPenguinPlugin::includeFile() const
{
    return QLatin1String("magicpenguin.h");
}
