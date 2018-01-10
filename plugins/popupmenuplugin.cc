#include "database/popupmenu.h"
#include "popupmenuplugin.h"

#include <QtPlugin>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QDesignerPropertySheetExtension>
#include <QtDesigner/QDesignerFormEditorInterface>

PopupMenuPlugin::PopupMenuPlugin(QObject *parent)
    : QObject(parent)
{
}

void PopupMenuPlugin::initialize(QDesignerFormEditorInterface * /*formEditor*/)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

bool PopupMenuPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *PopupMenuPlugin::createWidget(QWidget *parent)
{
    return new PopupMenu(parent);
}

QString PopupMenuPlugin::name() const
{
    return QStringLiteral("PopupMenu");
}

QString PopupMenuPlugin::group() const
{
    return QStringLiteral("Display Widgets [kallup]");
}

QIcon PopupMenuPlugin::icon() const
{
    return QIcon(":/img/dbsql.png");
}

QString PopupMenuPlugin::toolTip() const
{
    return QString();
}

QString PopupMenuPlugin::whatsThis() const
{
    return QString();
}

bool PopupMenuPlugin::isContainer() const
{
    return false;
}

QString PopupMenuPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"PopupMenu\" name=\"popupMenu\">\n"
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

QString PopupMenuPlugin::includeFile() const
{
    return QStringLiteral("popupmenu.h");
}

