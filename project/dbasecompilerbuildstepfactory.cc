#include "dbasebuildconfiguration.h"
#include "dbasecompilerbuildstep.h"
#include "dbasecompilerbuildstepfactory.h"

#include "../plugins/dbasepluginconstants.h"

#include <projectexplorer/projectexplorerconstants.h>
#include <utils/qtcassert.h>

#include <memory>

using namespace ProjectExplorer;

namespace dBase {

dBaseCompilerBuildStepFactory::dBaseCompilerBuildStepFactory(QObject *parent)
    : IBuildStepFactory(parent)
{}

QList<BuildStepInfo> dBaseCompilerBuildStepFactory::availableSteps(BuildStepList *parent) const
{
    if (parent->id() != ProjectExplorer::Constants::BUILDSTEPS_BUILD)
        return {};

    auto bc = qobject_cast<dBaseBuildConfiguration *>(parent->parent());
    if (!bc || bc->hasdBaseCompilerBuildStep())
        return {};

    return {{Constants::C_DBASECOMPILERBUILDSTEP_ID, tr("dBase Compiler Build Step")}};
}

BuildStep *dBaseCompilerBuildStepFactory::create(BuildStepList *parent, Core::Id)
{
    return new dBaseCompilerBuildStep(parent);
}

BuildStep *dBaseCompilerBuildStepFactory::clone(BuildStepList *parent, BuildStep *buildStep)
{
    QTC_ASSERT(parent, return nullptr);
    QTC_ASSERT(buildStep, return nullptr);
    std::unique_ptr<dBaseCompilerBuildStep> result(new dBaseCompilerBuildStep(parent));
    return result->fromMap(buildStep->toMap()) ? result.release() : nullptr;
}

}  // namespace: dBase
