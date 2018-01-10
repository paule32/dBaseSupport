#ifndef DBASECOMPILERBUILDSTEPFACTORY_H_
#define DBASECOMPILERBUILDSTEPFACTORY_H_
#pragma once

#include <projectexplorer/buildstep.h>

namespace dBase {

class dBaseCompilerBuildStepFactory : public ProjectExplorer::IBuildStepFactory
{
    Q_OBJECT

public:
    dBaseCompilerBuildStepFactory(QObject *parent = nullptr);

    QList<ProjectExplorer::BuildStepInfo>
        availableSteps(ProjectExplorer::BuildStepList *parent) const override;

    ProjectExplorer::BuildStep *create(ProjectExplorer::BuildStepList *parent, Core::Id id) override;
    ProjectExplorer::BuildStep *clone(ProjectExplorer::BuildStepList *parent, ProjectExplorer::BuildStep *product) override;
};

}  // namespace: dBase
#endif
