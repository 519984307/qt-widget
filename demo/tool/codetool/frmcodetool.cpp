#pragma execution_character_set("utf-8")

#include "frmcodetool.h"
#include "ui_frmcodetool.h"
#include "qfiledialog.h"
#include "qfile.h"

frmCodeTool::frmCodeTool(QWidget *parent) : QWidget(parent), ui(new Ui::frmCodeTool)
{
    ui->setupUi(this);
}

frmCodeTool::~frmCodeTool()
{
    delete ui;
}

void frmCodeTool::newHeader(const QString &fileName)
{
    QString name = ui->txtName->text().trimmed();
    QStringList list;
    list << QString("#ifndef %1PLUGIN_H").arg(name.toUpper());
    list << QString("#define %1PLUGIN_H").arg(name.toUpper());
    list << QString("");
    list << QString("#include <QDesignerCustomWidgetInterface>");
    list << QString("");
    list << QString("class %1Plugin : public QObject, public QDesignerCustomWidgetInterface").arg(name);
    list << QString("{");
    list << QString("    Q_OBJECT");
    list << QString("    Q_INTERFACES(QDesignerCustomWidgetInterface)");
    list << QString("");
    list << QString("public:");
    list << QString("    %1Plugin(QObject *parent = 0);").arg(name);
    list << QString("");
    list << QString("    bool isContainer() const;");
    list << QString("    bool isInitialized() const;");
    list << QString("    QIcon icon() const;");
    list << QString("    QString domXml() const;");
    list << QString("    QString group() const;");
    list << QString("    QString includeFile() const;");
    list << QString("    QString name() const;");
    list << QString("    QString toolTip() const;");
    list << QString("    QString whatsThis() const;");
    list << QString("    QWidget *createWidget(QWidget *parent);");
    list << QString("    void initialize(QDesignerFormEditorInterface *core);");
    list << QString("");
    list << QString("private:");
    list << QString("    bool m_initialized;");
    list << QString("};");
    list << QString("");
    list << QString("#endif");

    QString content = list.join("\n");
    ui->txtHeader->setText(content);

    //保存到文件
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        file.write(content.toLatin1());
        file.close();
    }
}

void frmCodeTool::newSource(const QString &fileName)
{
    QString name = ui->txtName->text().trimmed();
    QStringList list;
    list << QString("#include \"%1.h\"").arg(name.toLower());
    list << QString("#include \"%1plugin.h\"").arg(name.toLower());
    list << QString("");
    list << QString("#include <QtPlugin>");
    list << QString("");
    list << QString("%1Plugin::%1Plugin(QObject *parent) : QObject(parent)").arg(name);
    list << QString("{");
    list << QString("    m_initialized = false;");
    list << QString("}");
    list << QString("");
    list << QString("void %1Plugin::initialize(QDesignerFormEditorInterface * /* core */)").arg(name);
    list << QString("{");
    list << QString("    if (m_initialized) {");
    list << QString("        return;");
    list << QString("    }");
    list << QString("");
    list << QString("    // Add extension registrations, etc. here");
    list << QString("");
    list << QString("    m_initialized = true;");
    list << QString("}");
    list << QString("");
    list << QString("bool %1Plugin::isInitialized() const").arg(name);
    list << QString("{");
    list << QString("    return m_initialized;");
    list << QString("}");
    list << QString("");
    list << QString("QWidget *%1Plugin::createWidget(QWidget *parent)").arg(name);
    list << QString("{");
    list << QString("    return new %1(parent);").arg(name);
    list << QString("}");
    list << QString("");
    list << QString("QString %1Plugin::name() const").arg(name);
    list << QString("{");
    list << QString("    return QLatin1String(\"%1\");").arg(name);
    list << QString("}");
    list << QString("");
    list << QString("QString %1Plugin::group() const").arg(name);
    list << QString("{");
    list << QString("    return QLatin1String(\"Quc Widgets\");");
    list << QString("}");
    list << QString("");
    list << QString("QIcon %1Plugin::icon() const").arg(name);
    list << QString("{");
    list << QString("    return QIcon(QLatin1String(\":/icon/%1.png\"));").arg(name.toLower());
    list << QString("}");
    list << QString("");
    list << QString("QString %1Plugin::toolTip() const").arg(name);
    list << QString("{");
    list << QString("    return QLatin1String(\"\");");
    list << QString("}");
    list << QString("");
    list << QString("QString %1Plugin::whatsThis() const").arg(name);
    list << QString("{");
    list << QString("    return QLatin1String(\"\");");
    list << QString("}");
    list << QString("");
    list << QString("bool %1Plugin::isContainer() const").arg(name);
    list << QString("{");
    list << QString("    return false;");
    list << QString("}");
    list << QString("");
    list << QString("QString %1Plugin::domXml() const").arg(name);
    list << QString("{");
    //首字母小写
    QString className = QString("%1%2").arg(name.mid(0, 1).toLower()).arg(name.mid(1, name.length() - 1));
    QString xml = QString("\"<widget class=%1\"%2%1\" name=%1\"%3%1\">\\n</widget>\\n\"").arg("\\").arg(name).arg(className);
    list << QString("    return QLatin1String(%1);").arg(xml);
    list << QString("}");
    list << QString("");
    list << QString("QString %1Plugin::includeFile() const").arg(name);
    list << QString("{");
    list << QString("    return QLatin1String(\"%1.h\");").arg(name.toLower());
    list << QString("}");
    list << QString("");

    QString content = list.join("\n");
    ui->txtSource->setText(content);

    //保存到文件
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        file.write(content.toLatin1());
        file.close();
    }
}

void frmCodeTool::on_btnSelect_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    if (!path.isEmpty()) {
        ui->txtPath->setText(path);
    }
}

void frmCodeTool::on_btnDo_clicked()
{
    QString path = ui->txtPath->text().trimmed();
    QString name = ui->txtName->text().trimmed().toLower();
    newHeader(path + "/" + name + "plugin.h");
    newSource(path + "/" + name + "plugin.cpp");
}
