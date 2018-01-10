#ifndef DBASEBUILDCONFIGURATION_H_
#define DBASEBUILDCONFIGURATION_H_
#pragma once

#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/target.h>

#include <QPointer>

namespace dBase {

class dBaseProject;
class dBaseCompilerBuildStep;

class dBaseBuildConfiguration : public ProjectExplorer::BuildConfiguration
{
    Q_OBJECT

public:
    dBaseBuildConfiguration(ProjectExplorer::Target *target);

    ProjectExplorer::NamedWidget *createConfigWidget() override;

    ProjectExplorer::BuildConfiguration::BuildType buildType() const override;

    bool fromMap(const QVariantMap &map) override;
    QVariantMap toMap() const override;

    Utils::FileName cacheDirectory() const;
    Utils::FileName outFilePath() const;

    static bool canRestore(const QVariantMap &map);

    bool hasdBaseCompilerBuildStep() const;
    bool hasdBaseCompilerCleanStep() const;

signals:
    void outFilePathChanged(const Utils::FileName &outFilePath);

private:
    const dBaseCompilerBuildStep *dbaseCompilerBuildStep() const;
};

}  // namespace: dBase
#endif
