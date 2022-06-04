#include "tasktableview.h"
#include "tasktableviewplugin.h"

#include <QtPlugin>

TaskTableViewPlugin::TaskTableViewPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void TaskTableViewPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TaskTableViewPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TaskTableViewPlugin::createWidget(QWidget *parent)
{
    return new TaskTableView(parent);
}

QString TaskTableViewPlugin::name() const
{
    return QLatin1String("TaskTableView");
}

QString TaskTableViewPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon TaskTableViewPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon/tasktableview.png"));
}

QString TaskTableViewPlugin::toolTip() const
{
    return QLatin1String("");
}

QString TaskTableViewPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool TaskTableViewPlugin::isContainer() const
{
    return false;
}

QString TaskTableViewPlugin::domXml() const
{
    return QLatin1String("<widget class=\"TaskTableView\" name=\"taskTableView\">\n</widget>\n");
}

QString TaskTableViewPlugin::includeFile() const
{
    return QLatin1String("tasktableview.h");
}
