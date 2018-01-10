#ifndef DBASERUNCONFIGURATION_H_
#define DBASERUNCONFIGURATION_H_
#pragma once

#include <projectexplorer/runconfiguration.h>

namespace ProjectExplorer {
class WorkingDirectoryAspect;
class ArgumentsAspect;
class TerminalAspect;
class LocalEnvironmentAspect;
}

namespace dBase {
class dBaseBuildConfiguration;
class dBaseRunConfiguration  : public ProjectExplorer::RunConfiguration
{
    Q_OBJECT
public:
    explicit dBaseRunConfiguration(ProjectExplorer::Target *target);
    
    QWidget *createConfigurationWidget() override;
    ProjectExplorer::Runnable runnable() const override;
    QVariantMap toMap() const  override;
    bool fromMap(const QVariantMap &map) override;
    
signals:
    void executableChanged(const QString);
    void runModeChanged(ProjectExplorer::ApplicationLauncher::Mode);
    void workingDirectoryChanged(const QString &workingDirectory);
    void commandLineArgumentsChanged(const QString &args);
    void runInTerminalChanged(bool);
    
private:
    void setExecutable(const QString &path);
    void setWorkingDirectory(const QString &path);
    void setCommandLineArguments(const QString &args);
    void updateConfiguration();
    void setActiveBuildConfiguration(dBaseBuildConfiguration *activeBuildConfiguration);
    
    QString m_executable;
    dBaseBuildConfiguration *m_buildConfiguration = nullptr;
    
    ProjectExplorer::WorkingDirectoryAspect* m_workingDirectoryAspect;
    ProjectExplorer::ArgumentsAspect* m_argumentAspect;
    ProjectExplorer::TerminalAspect* m_terminalAspect;
    ProjectExplorer::LocalEnvironmentAspect* m_localEnvironmentAspect;
};

}  // namespace: dBase

#endif  // DBASERUNCONFIGURATION_H_
