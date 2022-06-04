#ifndef QUCPLUGIN_H
#define QUCPLUGIN_H

#include <QtDesigner>
#include <qplugin.h>

class QucPlugin : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
#endif // QT_VERSION >= 0x050000

public:
    explicit QucPlugin(QObject *parent = 0);

    virtual QList<QDesignerCustomWidgetInterface *> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface *> widgets;
};

#endif
