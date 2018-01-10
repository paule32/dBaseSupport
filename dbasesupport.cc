#include "plugins/popupmenuplugin.h"
#include "plugins/dbsqlplugin.h"
#include "dbasesupport.h"

dbasesupport::dbasesupport(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new PopupMenuPlugin(this));
    m_widgets.append(new dbSQLPlugin(this));
    
}

QList<QDesignerCustomWidgetInterface*> dbasesupport::customWidgets() const
{
    return m_widgets;
}
