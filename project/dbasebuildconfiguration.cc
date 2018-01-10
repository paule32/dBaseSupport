#include "dbasebuildconfiguration.h"
#include "dbasebuildconfigurationwidget.h"
#include "dbasecompilerbuildstep.h"
#include "dbaseproject.h"

#include "../plugins/dbasepluginconstants.h"

#include <projectexplorer/namedwidget.h>
#include <projectexplorer/projectexplorerconstants.h>
#include <projectexplorer/buildsteplist.h>

#include <utils/qtcassert.h>

using namespace ProjectExplorer;
using namespace Utils;

namespace dBase {

dBaseBuildConfiguration::dBaseBuildConfiguration(Target *target)
    : BuildConfiguration(target, Constants::C_DBASEBUILDCONFIGURATION_ID)
{}

NamedWidget *dBaseBuildConfiguration::createConfigWidget()
{
    return new dBaseBuildConfigurationWidget(this);
}

BuildConfiguration::BuildType dBaseBuildConfiguration::buildType() const
{
    return BuildConfiguration::Unknown;
}

bool dBaseBuildConfiguration::fromMap(const QVariantMap &map)
{
    if (!BuildConfiguration::fromMap(map))
        return false;

    if (!canRestore(map))
        return false;

    const QString displayName = map[Constants::C_DBASEBUILDCONFIGURATION_DISPLAY_KEY].toString();
    const QString buildDirectory = map[Constants::C_DBASEBUILDCONFIGURATION_BUILDDIRECTORY_KEY].toString();

    setDisplayName(displayName);
    setBuildDirectory(FileName::fromString(buildDirectory));

    return true;
}

QVariantMap dBaseBuildConfiguration::toMap() const
{
    QVariantMap result = BuildConfiguration::toMap();
    result[Constants::C_DBASEBUILDCONFIGURATION_DISPLAY_KEY] = displayName();
    result[Constants::C_DBASEBUILDCONFIGURATION_BUILDDIRECTORY_KEY] = buildDirectory().toString();
    return result;
}

FileName dBaseBuildConfiguration::cacheDirectory() const
{
    return buildDirectory().appendPath(QStringLiteral("dbasecache"));
}

FileName dBaseBuildConfiguration::outFilePath() const
{
    const dBaseCompilerBuildStep *step = dbaseCompilerBuildStep();
    QTC_ASSERT(step, return FileName());
    return step->outFilePath();
}

bool dBaseBuildConfiguration::canRestore(const QVariantMap &map)
{
    return idFromMap(map) == Constants::C_DBASEBUILDCONFIGURATION_ID;
}

bool dBaseBuildConfiguration::hasdBaseCompilerBuildStep() const
{
    BuildStepList *steps = stepList(ProjectExplorer::Constants::BUILDSTEPS_BUILD);
    return steps ? steps->contains(Constants::C_DBASECOMPILERBUILDSTEP_ID) : false;
}

bool dBaseBuildConfiguration::hasdBaseCompilerCleanStep() const
{
    BuildStepList *steps = stepList(ProjectExplorer::Constants::BUILDSTEPS_CLEAN);
    return steps ? steps->contains(Constants::C_DBASECOMPILERCLEANSTEP_ID) : false;
}

const dBaseCompilerBuildStep *dBaseBuildConfiguration::dbaseCompilerBuildStep() const
{
    BuildStepList *steps = stepList(ProjectExplorer::Constants::BUILDSTEPS_BUILD);
    QTC_ASSERT(steps, return nullptr);
    foreach (BuildStep *step, steps->steps())
        if (step->id() == Constants::C_DBASECOMPILERBUILDSTEP_ID)
            return qobject_cast<dBaseCompilerBuildStep *>(step);
    return nullptr;
}

}  // namespace: dBase
