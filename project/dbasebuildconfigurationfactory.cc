#include "dbasebuildconfigurationfactory.h"
#include "dbasebuildconfiguration.h"
#include "dbasecompilerbuildstep.h"
#include "dbasecompilercleanstep.h"
#include "dbaseproject.h"

#include "../plugins/dbasepluginconstants.h"

#include <coreplugin/documentmanager.h>
#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/buildinfo.h>
#include <projectexplorer/buildsteplist.h>
#include <projectexplorer/buildstep.h>
#include <projectexplorer/kit.h>
#include <projectexplorer/projectexplorerconstants.h>
#include <projectexplorer/projectmacroexpander.h>
#include <projectexplorer/target.h>

#include <utils/mimetypes/mimedatabase.h>
#include <utils/qtcassert.h>

#include <memory>

using namespace ProjectExplorer;
using namespace Utils;

namespace dBase {

dBaseBuildConfigurationFactory::dBaseBuildConfigurationFactory(QObject *parent)
    : IBuildConfigurationFactory(parent)
{}

QList<BuildInfo *> dBaseBuildConfigurationFactory::availableBuilds(const Target *parent) const
{
    // Retrieve the project path
    auto project = qobject_cast<dBaseProject *>(parent->project());
    QTC_ASSERT(project, return {});

    // Create the build info
    BuildInfo *info = createBuildInfo(parent->kit(), project->projectFilePath().toString(),
                                      BuildConfiguration::Debug);

    info->displayName.clear(); // ask for a name
    info->buildDirectory.clear(); // This depends on the displayName

    return {info};
}

QList<BuildInfo *> dBaseBuildConfigurationFactory::availableSetups(const Kit *k, const QString &projectPath) const
{
    BuildInfo *debug = createBuildInfo(k, projectPath, BuildConfiguration::Debug);
    BuildInfo *release = createBuildInfo(k, projectPath, BuildConfiguration::Release);
    return {debug, release};
}

BuildConfiguration *dBaseBuildConfigurationFactory::create(Target *parent, const BuildInfo *info) const
{
    auto project = qobject_cast<dBaseProject *>(parent->project());
    QTC_ASSERT(project, return nullptr);

    // Create the build configuration and initialize it from build info
    auto result = new dBaseBuildConfiguration(parent);
    result->setDisplayName(info->displayName);
    result->setDefaultDisplayName(info->displayName);
    result->setBuildDirectory(defaultBuildDirectory(parent->kit(),
                                                    project->projectFilePath().toString(),
                                                    info->displayName,
                                                    info->buildType));

    // Add dBase compiler build step
    {
        BuildStepList *buildSteps = result->stepList(Core::Id(ProjectExplorer::Constants::BUILDSTEPS_BUILD));
        auto dbaseCompilerBuildStep = new dBaseCompilerBuildStep(buildSteps);
        dBaseCompilerBuildStep::DefaultBuildOptions defaultOption;
        switch (info->buildType) {
        case BuildConfiguration::Release:
            defaultOption = dBaseCompilerBuildStep::DefaultBuildOptions::Release;
            break;
        case BuildConfiguration::Debug:
            defaultOption = dBaseCompilerBuildStep::DefaultBuildOptions::Debug;
            break;
        default:
            defaultOption = dBaseCompilerBuildStep::DefaultBuildOptions::Empty;
            break;
        }
        dbaseCompilerBuildStep->setDefaultCompilerOptions(defaultOption);
        Utils::FileNameList dbaseFiles = project->dbaseFiles();
        if (!dbaseFiles.isEmpty())
            dbaseCompilerBuildStep->setTargetdBaseFile(dbaseFiles.first());
        buildSteps->appendStep(dbaseCompilerBuildStep);
    }

    // Add clean step
    {
        BuildStepList *cleanSteps = result->stepList(Core::Id(ProjectExplorer::Constants::BUILDSTEPS_CLEAN));
        cleanSteps->appendStep(new dBaseCompilerCleanStep(cleanSteps));
    }

    return result;
}

bool dBaseBuildConfigurationFactory::canRestore(const Target *parent, const QVariantMap &map) const
{
    Q_UNUSED(parent);
    if (!canHandle(parent))
        return false;
    return dBaseBuildConfiguration::canRestore(map);
}

BuildConfiguration *dBaseBuildConfigurationFactory::restore(Target *parent, const QVariantMap &map)
{
    QTC_ASSERT(canRestore(parent, map), return nullptr);

    // Create the build configuration
    auto result = new dBaseBuildConfiguration(parent);

    // Restore from map
    bool status = result->fromMap(map);
    QTC_ASSERT(status, return nullptr);

    return result;
}

bool dBaseBuildConfigurationFactory::canClone(const Target *parent, BuildConfiguration *product) const
{
    QTC_ASSERT(parent, return false);
    QTC_ASSERT(product, return false);
    if (!canHandle(parent))
        return false;
    return product->id() == Constants::C_DBASEBUILDCONFIGURATION_ID;
}

BuildConfiguration *dBaseBuildConfigurationFactory::clone(Target *parent, BuildConfiguration *product)
{
    QTC_ASSERT(parent, return nullptr);
    QTC_ASSERT(product, return nullptr);
    auto buildConfiguration = qobject_cast<dBaseBuildConfiguration *>(product);
    QTC_ASSERT(buildConfiguration, return nullptr);
    std::unique_ptr<dBaseBuildConfiguration> result(new dBaseBuildConfiguration(parent));
    return result->fromMap(buildConfiguration->toMap()) ? result.release() : nullptr;
}

int dBaseBuildConfigurationFactory::priority(const Kit *k, const QString &projectPath) const
{
    if (k && Utils::mimeTypeForFile(projectPath).matchesName(Constants::C_DBASE_PROJECT_MIMETYPE))
        return 0;
    return -1;
}

int dBaseBuildConfigurationFactory::priority(const Target *parent) const
{
    return canHandle(parent) ? 0 : -1;
}

bool dBaseBuildConfigurationFactory::canHandle(const Target *t) const
{
    if (!t->project()->supportsKit(t->kit()))
        return false;
    return qobject_cast<dBaseProject *>(t->project());
}

FileName dBaseBuildConfigurationFactory::defaultBuildDirectory(const Kit *k,
                                                               const QString &projectFilePath,
                                                               const QString &bc,
                                                               BuildConfiguration::BuildType buildType)
{
    QFileInfo projectFileInfo(projectFilePath);

    ProjectMacroExpander expander(projectFilePath, projectFileInfo.baseName(), k, bc, buildType);
    QString buildDirectory = expander.expand(Core::DocumentManager::buildDirectory());

    if (FileUtils::isAbsolutePath(buildDirectory))
        return FileName::fromString(buildDirectory);

    auto projectDir = FileName::fromString(projectFileInfo.absoluteDir().absolutePath());
    auto result = projectDir.appendPath(buildDirectory);

    return result;
}

BuildInfo *dBaseBuildConfigurationFactory::createBuildInfo(const Kit *k, const QString &projectFilePath,
                                                         BuildConfiguration::BuildType buildType) const
{
    auto result = new BuildInfo(this);
    result->buildType = buildType;
    result->displayName = BuildConfiguration::buildTypeName(buildType);
    result->buildDirectory = defaultBuildDirectory(k, projectFilePath, result->displayName, buildType);
    result->kitId = k->id();
    result->typeName = tr("Build");
    return result;
}

} // namespace dBase
