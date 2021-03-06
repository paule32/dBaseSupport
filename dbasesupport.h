#ifndef DBASESUPPORT_H
#define DBASESUPPORT_H

#include <QtDesigner>
#include <qplugin.h>

namespace dBase {
class dBaseSupport : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
    
public:
    explicit dBaseSupport(QObject *parent = 0);
    
    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;
    
private:
    QList<QDesignerCustomWidgetInterface*> m_widgets;
};
}  // namespace: dBase
#endif
