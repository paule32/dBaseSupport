#ifndef DBASECONFIGURATIONFACTORY_H_
#define DBASECONFIGURATIONFACTORY_H_
#pragma once

#include <projectexplorer/runconfiguration.h>

namespace dBase {
class dBaseRunConfigurationFactory
    : public ProjectExplorer::IRunConfigurationFactory
{
public:
    dBaseRunConfigurationFactory();
    QString displayNameForId(Core::Id id) const override;
    
    QList<Core::Id> availableCreationIds(
    ProjectExplorer::Target *parent,
    CreationMode mode) const override;
    
    bool canClone(
    ProjectExplorer::Target *parent,
    ProjectExplorer::RunConfiguration *product) const override;
    
    bool canCreate(
    ProjectExplorer::Target *parent,
    Core::Id id) const override;
    
    bool canRestore(
    ProjectExplorer::Target *parent,
    const QVariantMap &map) const override;
    
    ProjectExplorer::RunConfiguration *clone(
    ProjectExplorer::Target *parent,
    ProjectExplorer::RunConfiguration *product) override;
    
private:
    bool canHandle(ProjectExplorer::Target *parent) const;
    
    ProjectExplorer::RunConfiguration *doCreate (ProjectExplorer::Target *parent, Core::Id id) override;
    ProjectExplorer::RunConfiguration *doRestore(ProjectExplorer::Target *parent, const QVariantMap &map) override;
};

}  // namespace: dBase

#endif  // DBASECONFIGURATIONFACTORY_H_
