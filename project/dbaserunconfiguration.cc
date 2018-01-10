#include "dbaserunconfiguration.h"
#include "dbasebuildconfiguration.h"
#include "dbaserunconfigurationwidget.h"

#include "../plugins/dbasepluginconstants.h"

#include <projectexplorer/runnables.h>
#include <projectexplorer/localenvironmentaspect.h>
#include <projectexplorer/runconfigurationaspects.h>

#include <utils/environment.h>

#include <QDir>
#include <QFileInfo>
#include <QVariantMap>

using namespace ProjectExplorer;
using namespace Utils;

namespace dBase {

dBaseRunConfiguration::dBaseRunConfiguration(Target *target)
    : RunConfiguration(target)
    , m_workingDirectoryAspect(new WorkingDirectoryAspect(this,dBase::Constants::C_DBASERUNCONFIGURATION_WORKINGDIRECTORYASPECT_ID))
    , m_argumentAspect(new ArgumentsAspect(this, dBase::Constants::C_DBASERUNCONFIGURATION_ARGUMENTASPECT_ID))
    , m_terminalAspect(new TerminalAspect (this, dBase::Constants::C_DBASERUNCONFIGURATION_TERMINALASPECT_ID))
    , m_localEnvironmentAspect(new LocalEnvironmentAspect(this, LocalEnvironmentAspect::BaseEnvironmentModifier()))
{
    m_terminalAspect->setRunMode(ApplicationLauncher::Gui);
    
    addExtraAspect(m_argumentAspect);
    addExtraAspect(m_terminalAspect);
    addExtraAspect(m_localEnvironmentAspect);
    
    setDisplayName(tr(Constants::C_DBASERUNCONFIGURATION_DISPLAY));
    setDefaultDisplayName(tr(Constants::C_DBASERUNCONFIGURATION_DEFAULT_DISPLAY));
    
    // connect target signals
    connect(target, &Target::activeBuildConfigurationChanged,
            this, &dBaseRunConfiguration::updateConfiguration);
    updateConfiguration();
}

QWidget *dBaseRunConfiguration::createConfigurationWidget()
{
    return new dBaseRunConfigurationWidget(this);
}

Runnable dBaseRunConfiguration::runnable() const
{
    StandardRunnable result;
    result.runMode = m_terminalAspect->runMode();
    result.executable = m_executable;
    result.commandLineArguments = m_argumentAspect->arguments();
    result.workingDirectory = m_workingDirectoryAspect->workingDirectory().toString();
    result.environment = m_localEnvironmentAspect->environment();
    return result;
}


QVariantMap dBaseRunConfiguration::toMap() const
{
    auto result = RunConfiguration::toMap();
    result[Constants::C_DBASERUNCONFIGURATION_EXECUTABLE_KEY] = m_executable;
    return result;
}

bool dBaseRunConfiguration::fromMap(const QVariantMap &map)
{
    bool result = RunConfiguration::fromMap(map);
    if (!result)
        return result;
    m_executable = map[Constants::C_DBASERUNCONFIGURATION_EXECUTABLE_KEY].toString();
    return true;
}

void dBaseRunConfiguration::setExecutable(const QString &executable)
{
    if (m_executable == executable)
        return;
    m_executable = executable;
    emit executableChanged(executable);
}

void dBaseRunConfiguration::setWorkingDirectory(const QString &workingDirectory)
{
    m_workingDirectoryAspect->setDefaultWorkingDirectory(FileName::fromString(workingDirectory));
}

void dBaseRunConfiguration::updateConfiguration()
{
    auto buildConfiguration = qobject_cast<dBaseBuildConfiguration *>(activeBuildConfiguration());
    QTC_ASSERT(buildConfiguration, return);
    setActiveBuildConfiguration(buildConfiguration);
    const QFileInfo outFileInfo = buildConfiguration->outFilePath().toFileInfo();
    setExecutable(outFileInfo.absoluteFilePath());
    setWorkingDirectory(outFileInfo.absoluteDir().absolutePath());
}


void dBaseRunConfiguration::setActiveBuildConfiguration(dBaseBuildConfiguration *activeBuildConfiguration)
{
    if (m_buildConfiguration == activeBuildConfiguration)
        return;

    if (m_buildConfiguration) {
        disconnect(m_buildConfiguration, &dBaseBuildConfiguration::buildDirectoryChanged,
                   this, &dBaseRunConfiguration::updateConfiguration);
        disconnect(m_buildConfiguration, &dBaseBuildConfiguration::outFilePathChanged,
                   this, &dBaseRunConfiguration::updateConfiguration);
    }

    m_buildConfiguration = activeBuildConfiguration;

    if (m_buildConfiguration) {
        connect(m_buildConfiguration, &dBaseBuildConfiguration::buildDirectoryChanged,
                this, &dBaseRunConfiguration::updateConfiguration);
        connect(m_buildConfiguration, &dBaseBuildConfiguration::outFilePathChanged,
                this, &dBaseRunConfiguration::updateConfiguration);
    }
}

}  // namespace: dBase
