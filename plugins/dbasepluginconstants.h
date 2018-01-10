#ifndef DBASEPLUGINCONSTANTS_H_
#define DBASEPLUGINCONSTANTS_H_
#pragma once

#include <QObject>
#include <QtGlobal>

namespace dBase {
namespace Constants {

const char C_DBASEPROJECT_ID[] = "dBase.dBaseProject";
const char C_DBASEEDITOR_ID [] = "dBase.dBaseEditor";
const char C_EDITOR_DISPLAY_NAME[] = QT_TRANSLATE_NOOP("OpenWith::Editors", "dBase Editor");
const char C_DBASE_ICON_PATH[] = ":/img/dbase.png";

// dBaseToolChain
const char C_DBASETOOLCHAIN_TYPEID[] = "dBase.dBaseToolChain";
const char C_DBASETOOLCHAIN_COMPILER_COMMAND_KEY[] = "dBase.dBaseToolChain.CompilerCommand";

// dBaseRunConfiguration
const char C_DBASERUNCONFIGURATION_ID[] = "dBase.dBaseRunConfiguration";
const char C_DBASERUNCONFIGURATION_DISPLAY[] = QT_TRANSLATE_NOOP("dBaseRunConfiguration", "Current Build Target");
const char C_DBASERUNCONFIGURATION_DEFAULT_DISPLAY[] = QT_TRANSLATE_NOOP("dBaseRunConfiguration", "Current Build Target");

const QString C_DBASERUNCONFIGURATION_EXECUTABLE_KEY = QStringLiteral("dBase.dBaseRunConfiguration.Executable");
const QString C_DBASERUNCONFIGURATION_WORKINGDIRECTORY_KEY = QStringLiteral("dBase.dBaseRunConfiguration.WorkingDirectory");
const QString C_DBASERUNCONFIGURATION_COMMANDLINEARGS_KEY = QStringLiteral("dBase.dBaseRunConfiguration.CommandlineArgs");
const QString C_DBASERUNCONFIGURATION_RUNMODE_KEY = QStringLiteral("dBase.dBaseRunConfiguration.RunMode");

const QString C_DBASERUNCONFIGURATION_WORKINGDIRECTORYASPECT_ID = QStringLiteral("dBase.dBaseRunConfiguration.WorkingDirectoryAspect");
const QString C_DBASERUNCONFIGURATION_ARGUMENTASPECT_ID = QStringLiteral("dBase.dBaseRunConfiguration.ArgumentAspect");
const QString C_DBASERUNCONFIGURATION_TERMINALASPECT_ID = QStringLiteral("dBase.dBaseRunConfiguration.TerminalAspect");

// dBaseProject
const char C_DBASEPROJECT_EXCLUDEDFILES[] = "dBase.dBaseProjectExcludedFiles";

// dBaseBuildConfiguration
const char C_DBASEBUILDCONFIGURATION_ID[] = "dBase.dBaseBuildConfiguration";
const QString C_DBASEBUILDCONFIGURATION_DISPLAY_KEY = QStringLiteral("dBase.dBaseBuildConfiguration.Display");
const QString C_DBASEBUILDCONFIGURATION_BUILDDIRECTORY_KEY = QStringLiteral("dBase.dBaseBuildConfiguration.BuildDirectory");

// dBaseBuildConfigurationWidget
const char C_DBASEBUILDCONFIGURATIONWIDGET_DISPLAY[] = QT_TRANSLATE_NOOP("dBaseBuildConfigurationWidget","General");

// dBaseCompilerBuildStep
const char C_DBASECOMPILERBUILDSTEP_ID[] = "dBase.dBaseCompilerBuildStep";
const char C_DBASECOMPILERBUILDSTEP_DISPLAY[] = QT_TRANSLATE_NOOP("dBaseCompilerBuildStep", "dBase Compiler Build Step");

const QString C_DBASECOMPILERBUILDSTEP_USERCOMPILEROPTIONS = QStringLiteral("dBase.dBaseCompilerBuildStep.UserCompilerOptions");
const QString C_DBASECOMPILERBUILDSTEP_DEFAULTBUILDOPTIONS = QStringLiteral("dBase.dBaseCompilerBuildStep.DefaultBuildOptions");

const QString C_DBASECOMPILERBUILDSTEP_TARGETDBASEFILE = QStringLiteral("dBase.dBaseCompilerBuildStep.TargetdBaseFile");

// dBaseCompilerBuildStepWidget
const char C_DBASECOMPILERBUILDSTEPWIDGET_DISPLAY[] = QT_TRANSLATE_NOOP("dBaseCompilerBuildStepConfigWidget", "dBase build step");
const char C_DBASECOMPILERBUILDSTEPWIDGET_SUMMARY[] = QT_TRANSLATE_NOOP("dBaseCompilerBuildStepConfigWidget", "dBase build step");

// dBaseCompilerCleanStep
const char C_DBASECOMPILERCLEANSTEP_ID[] = "dBase.dBaseCompilerCleanStep";
const char C_DBASECOMPILERCLEANSTEP_DISPLAY[] = QT_TRANSLATE_NOOP("dBaseCompilerCleanStepFactory", "dBase Compiler Clean Step");

// dBaseCompilerCleanStepWidget
const char C_DBASECOMPILERCLEANSTEPWIDGET_DISPLAY[] = QT_TRANSLATE_NOOP("dBaseCompilerCleanStepWidget", "dBase clean step");
const char C_DBASECOMPILERCLEANSTEPWIDGET_SUMMARY[] = QT_TRANSLATE_NOOP("dBaseCompilerCleanStepWidget", "dBase clean step");

const char C_DBASELANGUAGE_ID[] = "dBase";
const char C_DBASECODESTYLESETTINGSPAGE_ID[] = "dBase.dBaseCodeStyleSettings";
const char C_DBASECODESTYLESETTINGSPAGE_DISPLAY[] = QT_TRANSLATE_NOOP("dBaseCodeStyleSettingsPage", "Code Style");
const char C_DBASECODESTYLESETTINGSPAGE_CATEGORY[] = "Z.dBase";
const char C_DBASECODESTYLESETTINGSPAGE_CATEGORY_DISPLAY[] = QT_TRANSLATE_NOOP("dBaseCodeStyleSettingsPage", "dBase");
const char C_DBASELANGUAGE_NAME[] = QT_TRANSLATE_NOOP("dBaseCodeStylePreferencesFactory", "dBase");
const char C_DBASEGLOBALCODESTYLE_ID[] = "dBaseGlobal";

const QString C_DBASESNIPPETGROUP_ID = QStringLiteral("dBase.dBaseSnippetsGroup");

const char C_DBASECODESTYLEPREVIEWSNIPPET[] =
        "import os\n"
        "\n"
        "type Foo = ref object of RootObj\n"
        "  name: string\n"
        "  value: int \n"
        "\n"
        "proc newFoo(): Foo =\n"
        "  new(result)\n"
        "\n"
        "if isMainModule():\n"
        "  let foo = newFoo()\n"
        "  echo foo.name\n";

/*******************************************************************************
 * MIME type
 ******************************************************************************/
const char C_DBASE_MIMETYPE[] = "text/x-dbase";
const char C_DBASE_SCRIPT_MIMETYPE[] = "text/x-dbase-script";
const char C_DBASE_MIME_ICON[] = "text-x-dbase";
const char C_DBASE_PROJECT_MIMETYPE[] = "text/x-dbase-project";

}  // namespace: Constants
}  // namespace: dBasePlguin

#endif // DBASEPLUGINCONSTANTS_H_
