#ifndef DBASEPLUGIN_H
#define DBASEPLUGIN_H
#pragma once

#include <QString>
#include <QStringList>

#include <extensionsystem/iplugin.h>

namespace dBase {
class dBasePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "dbase.json")
    
public:
     dBasePlugin();
    ~dBasePlugin();
    
    bool initialize(const QStringList &arguments, QString *errorMessage) final;
    void extensionsInitialized() final;
};
}  // namespace: dBasePlugin

#endif // DBASEPLUGIN_H
