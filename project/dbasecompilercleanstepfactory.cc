#include "dbasecompilercleanstepfactory.h"
#include "dbasebuildconfiguration.h"
#include "dbasecompilercleanstep.h"

#include "../plugins/dbasepluginconstants.h"

#include <projectexplorer/projectexplorerconstants.h>

#include <memory>

using namespace ProjectExplorer;

namespace dBase {

dBaseCompilerCleanStepFactory::dBaseCompilerCleanStepFactory(QObject *parent)
    : IBuildStepFactory(parent)
{}

QList<BuildStepInfo> dBaseCompilerCleanStepFactory::availableSteps(BuildStepList *parent) const
{
    if (parent->id() != ProjectExplorer::Constants::BUILDSTEPS_CLEAN)
        return {};

    auto bc = qobject_cast<dBaseBuildConfiguration *>(parent->parent());
    if (!bc || bc->hasdBaseCompilerCleanStep())
        return {};

    return {{Constants::C_DBASECOMPILERCLEANSTEP_ID,
             tr(dBase::Constants::C_DBASECOMPILERCLEANSTEP_DISPLAY),
             BuildStepInfo::Unclonable}};
}

BuildStep *dBaseCompilerCleanStepFactory::create(BuildStepList *parent, Core::Id)
{
    return new dBaseCompilerCleanStep(parent);
}

BuildStep *dBaseCompilerCleanStepFactory::clone(BuildStepList *, BuildStep *)
{
    return nullptr;
}

}
