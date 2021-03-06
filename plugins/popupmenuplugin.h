#ifndef POPUPMENUPLUGIN_H
#define POPUPMENUPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

namespace dBase {
class PopupMenuPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
    
    
public:
    PopupMenuPlugin(QObject *parent = 0);
    
    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);
    
private:
    bool m_initialized;
};
}  // namespace: dBase
#endif
