#include "dbaseplugin.h"

#include "dbasepluginconstants.h"

#include "editor/dbaseeditorfactory.h"
#include "editor/dbasehighlighter.h"

#include "project/dbaseproject.h"
#include "project/dbaserunconfiguration.h"
#include "project/dbaserunconfigurationfactory.h"

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
    
    ProjectExplorer::ToolChainManager::registerLanguage(
    Constants::C_DBASELANGUAGE_ID,
    Constants::C_DBASELANGUAGE_NAME);
    
    RunControl::registerWorker<dBaseRunConfiguration,
    SimpleTargetRunner>
    (ProjectExplorer::Constants::NORMAL_RUN_MODE);
    
    
    TextEditor::SnippetProvider::registerGroup(
    Constants::C_DBASESNIPPETGROUP_ID,
    tr("dBase", "SnippetProvider"),
    &dBaseEditorFactory::decorateEditor);
    
    ProjectExplorer::ProjectManager::
    registerProjectType<dBaseProject>(
    Constants::C_DBASE_PROJECT_MIMETYPE);
    
    return true;
}

void dBasePlugin::extensionsInitialized()
{
    const QIcon icon((QLatin1String(Constants::C_DBASE_ICON_PATH)));
    if (!icon.isNull()) {
        Core::FileIconProvider::registerIconOverlayForMimeType(icon, Constants::C_DBASE_MIMETYPE);
        Core::FileIconProvider::registerIconOverlayForMimeType(icon, Constants::C_DBASE_SCRIPT_MIMETYPE);
    }
}
}  // namespace: dBasePlugin
