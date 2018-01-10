#include "plugins/popupmenuplugin.h"
#include "plugins/dbsqlplugin.h"
#include "dbasesupport.h"

namespace dBase {
dBaseSupport::dBaseSupport(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new PopupMenuPlugin(this));
    m_widgets.append(new dbSQLPlugin(this));
    
}

QList<QDesignerCustomWidgetInterface*> dBaseSupport::customWidgets() const
{
    return m_widgets;
}

}  // namespace: dBase
