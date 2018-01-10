#ifndef DBASECOMPILERCLEANSTEP_H_
#define DBASECOMPILERCLEANSTEP_H_
#pragma once

#include <projectexplorer/buildstep.h>
#include <projectexplorer/buildsteplist.h>
#include <utils/fileutils.h>

namespace dBase {

class dBaseCompilerCleanStep : public ProjectExplorer::BuildStep
{
    Q_OBJECT

public:
    dBaseCompilerCleanStep(ProjectExplorer::BuildStepList *parentList);

    ProjectExplorer::BuildStepConfigWidget *createConfigWidget() override;

    bool init(QList<const BuildStep *> &earlierSteps) override;

    void run(QFutureInterface<bool> &fi) override;

private:
    bool removeCacheDirectory();
    bool removeOutFilePath();

    Utils::FileName m_buildDir;
};

}  // namespace: dBase
#endif
