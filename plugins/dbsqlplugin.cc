#include "database/dbsql.h"
#include "dbsqlplugin.h"

#include "../database/popupmenu.h"
#include "popupmenuplugin.h"

#include <QtPlugin>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QDesignerPropertySheetExtension>
#include <QtDesigner/QDesignerFormEditorInterface>

namespace dBase {
dbSQLPlugin::dbSQLPlugin(QObject *parent)
    : QObject(parent)
{
}

void dbSQLPlugin::initialize(QDesignerFormEditorInterface * /*formEditor*/)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

bool dbSQLPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *dbSQLPlugin::createWidget(QWidget *parent)
{
    return new dbSQL(parent);
}

QString dbSQLPlugin::name() const
{
    return QStringLiteral("dbSQL");
}

QString dbSQLPlugin::group() const
{
    return QStringLiteral("Display Widgets [kallup]");
}

QIcon dbSQLPlugin::icon() const
{
    return QIcon(":/img/dbsql.png");
}

QString dbSQLPlugin::toolTip() const
{
    return QString();
}

QString dbSQLPlugin::whatsThis() const
{
    return QString();
}

bool dbSQLPlugin::isContainer() const
{
    return false;
}

QString dbSQLPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"dbSQL\" name=\"dbsql\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>32</width>\n"
           "    <height>32</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>";
}

QString dbSQLPlugin::includeFile() const
{
    return QStringLiteral("dbSQL.h");
}

}
