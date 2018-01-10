#ifndef DBASECOMPILERBUILDSTEP_H_
#define DBASECOMPILERBUILDSTEP_H_
#pragma once

#include <projectexplorer/abstractprocessstep.h>
#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/buildstep.h>
#include <projectexplorer/buildsteplist.h>

namespace dBase {

class dBaseCompilerBuildStep : public ProjectExplorer::AbstractProcessStep
{
    Q_OBJECT

public:
    enum DefaultBuildOptions { Empty = 0, Debug, Release};

    dBaseCompilerBuildStep(ProjectExplorer::BuildStepList *parentList);

    bool init(QList<const ProjectExplorer::BuildStep *> &earlierSteps) override;
    ProjectExplorer::BuildStepConfigWidget *createConfigWidget() override;

    bool fromMap(const QVariantMap &map) override;
    QVariantMap toMap() const override;

    QStringList userCompilerOptions() const;
    void setUserCompilerOptions(const QStringList &options);

    DefaultBuildOptions defaultCompilerOptions() const;
    void setDefaultCompilerOptions(DefaultBuildOptions options);

    Utils::FileName targetdBaseFile() const;
    void setTargetdBaseFile(const Utils::FileName &targetdBaseFile);

    Utils::FileName outFilePath() const;

signals:
    void userCompilerOptionsChanged(const QStringList &options);
    void defaultCompilerOptionsChanged(DefaultBuildOptions options);
    void targetdBaseFileChanged(const Utils::FileName &targetdBaseFile);
    void processParametersChanged();
    void outFilePathChanged(const Utils::FileName &outFilePath);

private:
    void setOutFilePath(const Utils::FileName &outFilePath);

    void updateOutFilePath();
    void updateProcessParameters();
    void updateCommand();
    void updateWorkingDirectory();
    void updateArguments();
    void updateEnvironment();

    void updateTargetdBaseFile();

    DefaultBuildOptions m_defaultOptions;
    QStringList m_userCompilerOptions;
    Utils::FileName m_targetdBaseFile;
    Utils::FileName m_outFilePath;
};

}  // namespace: dBase                                                                                                  
#endif
