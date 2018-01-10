#include "dbaseplugin.h"

#include "plugins/dbasepluginconstants.h"
#include "editor/dbaseeditorfactory.h"
#include "editor/dbasehighlighter.h"

#include "project/dbasebuildconfigurationfactory.h"
#include "project/dbasecompilerbuildstepfactory.h"
#include "project/dbasecompilercleanstepfactory.h"
#include "project/dbaseproject.h"
#include "project/dbaserunconfiguration.h"
#include "project/dbaserunconfigurationfactory.h"
#include "project/dbasetoolchainfactory.h"

#include "setting/nimcodestylepreferencesfactory.h"
#include "setting/nimcodestylesettingspage.h"
#include "setting/nimsettings.h"

#include <coreplugin/fileiconprovider.h>

#include <projectexplorer/projectmanager.h>
#include <projectexplorer/toolchainmanager.h>
#include <projectexplorer/runconfiguration.h>

#include <texteditor/snippets/snippetprovider.h>

#include <QtPlugin>

using namespace Utils;
using namespace ProjectExplorer;

namespace dBase {

static dBasePlugin *m_instance = 0;

dBasePlugin::dBasePlugin()
{
    m_instance = this;
}

dBasePlugin::~dBasePlugin()
{
    m_instance = 0;
}

bool dBasePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorMessage)

    ProjectExplorer::ToolChainManager::registerLanguage(Constants::C_DBASELANGUAGE_ID, Constants::C_DBASELANGUAGE_NAME);

    RunControl::registerWorker<dBaseRunConfiguration, SimpleTargetRunner>
            (ProjectExplorer::Constants::NORMAL_RUN_MODE);

    addAutoReleasedObject(new dBaseSettings);
    addAutoReleasedObject(new dBaseEditorFactory);
    addAutoReleasedObject(new dBaseBuildConfigurationFactory);
    addAutoReleasedObject(new dBaseRunConfigurationFactory);
    addAutoReleasedObject(new dBaseCompilerBuildStepFactory);
    addAutoReleasedObject(new dBaseCompilerCleanStepFactory);
    addAutoReleasedObject(new dBaseCodeStyleSettingsPage);
    addAutoReleasedObject(new dBaseCodeStylePreferencesFactory);
    addAutoReleasedObject(new dBaseToolChainFactory);

    TextEditor::SnippetProvider::registerGroup(Constants::C_DBASESNIPPETGROUP_ID,
                                               tr("dBase", "SnippetProvider"),
                                               &dBaseEditorFactory::decorateEditor);

    ProjectExplorer::ProjectManager::registerProjectType<dBaseProject>(Constants::C_DBASE_PROJECT_MIMETYPE);

    return true;
}

void dBasePlugin::extensionsInitialized()
{
    // Add MIME overlay icons (these icons displayed at Project dock panel)
    const QIcon icon((QLatin1String(dBase::Constants::C_DBASE_ICON_PATH)));
    if (!icon.isNull()) {
        Core::FileIconProvider::registerIconOverlayForMimeType(icon, Constants::C_DBASE_MIMETYPE);
        Core::FileIconProvider::registerIconOverlayForMimeType(icon, Constants::C_DBASE_SCRIPT_MIMETYPE);
    }
}

} // namespace dBase
