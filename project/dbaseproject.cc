#include "dbaseprojectnode.h"
#include "dbaseproject.h"
#include "dbasetoolchain.h"

#include "dbasebuildconfiguration.h"
#include "dbasetoolchain.h"

#include "../plugins/dbasepluginconstants.h"

#include <coreplugin/progressmanager/progressmanager.h>
#include <coreplugin/iversioncontrol.h>
#include <coreplugin/vcsmanager.h>

#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/kit.h>
#include <projectexplorer/projectexplorerconstants.h>
#include <projectexplorer/projectnodes.h>
#include <projectexplorer/target.h>
#include <projectexplorer/toolchain.h>
#include <projectexplorer/kitinformation.h>

#include <texteditor/textdocument.h>

#include <utils/algorithm.h>
#include <utils/qtcassert.h>
#include <utils/runextensions.h>

#include <QFileInfo>
#include <QQueue>

using namespace ProjectExplorer;
using namespace Utils;

namespace dBase {
const int MIN_TIME_BETWEEN_PROJECT_SCANS = 4500;

dBaseProject::dBaseProject(const FileName &fileName)
    : Project(Constants::C_DBASE_MIMETYPE, fileName)
{
    setId(Constants::C_DBASEPROJECT_ID);
    setDisplayName(fileName.toFileInfo().completeBaseName());
    
    m_projectScanTimer.setSingleShot(true);
    connect(
    &m_projectScanTimer,
    &QTimer::timeout, this,
    &dBaseProject::collectProjectFiles);
    
    connect(
    &m_futureWatcher,
    &QFutureWatcher<QList<FileNode *>>::finished, this,
    &dBaseProject::updateProject);
    
    collectProjectFiles();
}

bool dBaseProject::needsConfiguration() const {
    return targets().empty();
}

void dBaseProject::scheduleProjectScan()
{
    auto elapsedTime = m_lastProjectScan.elapsed();
    if (elapsedTime < MIN_TIME_BETWEEN_PROJECT_SCANS) {
        if (!m_projectScanTimer.isActive()) {
            m_projectScanTimer.setInterval(MIN_TIME_BETWEEN_PROJECT_SCANS - elapsedTime);
            m_projectScanTimer.start();
        }
    }   else {
        collectProjectFiles();
    }
}

bool dBaseProject::addFiles(const QStringList &filePaths)
{
    m_excludedFiles = Utils::filtered(m_excludedFiles,
    [&](const QString &f) {
        return !filePaths.contains(f);
    });
    
    scheduleProjectScan();
    return true;
}

bool dBaseProject::removeFiles(const QStringList &filePaths)
{
    m_excludedFiles.append(filePaths);
    m_excludedFiles = Utils::filteredUnique(m_excludedFiles);
    
    scheduleProjectScan();
    return true;
}

bool dBaseProject::renameFile(const QString &filePath, const QString &newFilePath)
{
    Q_UNUSED(filePath)
    m_excludedFiles.removeOne(newFilePath);
    
    scheduleProjectScan();
    return true;
}

void dBaseProject::collectProjectFiles()
{
    m_lastProjectScan.start();
    QTC_ASSERT(!m_futureWatcher.future().isRunning(), return);
    
    FileName prjDir = projectDirectory();
    
    const QList<Core::IVersionControl *> versionControls =
    Core::VcsManager::versionControls();
    
    QFuture<QList<ProjectExplorer::FileNode *>> future =
    Utils::runAsync([prjDir, versionControls] {
        return FileNode::scanForFilesWithVersionControls(
            prjDir, [](const FileName &fn) {
            return new FileNode(fn,FileType::Source, false);
            },
            versionControls);
    });
    
    m_futureWatcher.setFuture(future);
    Core::ProgressManager::addTask(future,
    tr("Scanning for dBase files"),
    "dBase.Project.Scan");
}

void dBaseProject::updateProject()
{
    emitParsingStarted();
    const QStringList oldFiles = m_files;
    m_files.clear();
    
    QList<FileNode *> fileNodes = Utils::filtered(
    m_futureWatcher.future().result(),
    [&](const FileNode *fn) {
        const FileName path = fn->filePath();
        const QString  fileName = path.fileName();
        const bool keep = !m_excludedFiles.contains(path.toString())
            && !fileName.endsWith(".dbproject", HostOsInfo::fileNameCaseSensitivity())
            && !fileName.contains(".dbproject.user", HostOsInfo::fileNameCaseSensitivity());
        if (!keep)
        delete fn;
        return keep;
    });
    
    m_files = Utils::transform(fileNodes,
    [](const FileNode *fn) {
        return fn->filePath().toString();
    });
    
    Utils::sort(m_files,
    [](const QString &a, const QString &b) {
        return a < b;
    });
    
    if (oldFiles == m_files)
    return;
    
    auto newRoot = new dBaseProjectNode(*this,projectDirectory());
    newRoot->setDisplayName(displayName());
    newRoot->addNestedNodes(fileNodes);
    
    setRootProjectNode(newRoot);
    emitParsingFinished(true);
}

bool dBaseProject::supportsKit(Kit *k, QString *errorMessage) const
{
    auto tc = dynamic_cast<dBaseToolChain *>(
    ToolChainKitInformation::toolChain(
    k, Constants::C_DBASELANGUAGE_ID));
    
    if (!tc) {
        if (errorMessage)
            *errorMessage = tr("No dBase compiler set");
        return false;
    }
    
    if (!tc->compilerCommand().exists()) {
        if (errorMessage)
            *errorMessage = tr("dBase Compiler does not exit.");
        return false;
    }   return true;
}

FileNameList dBaseProject::dbaseFiles() const
{
    const QStringList dbase = files(AllFiles,
    [](const ProjectExplorer::Node *n) {
        return n->filePath().endsWith(".prg");
    });
    return Utils::transform(dbase,
    [](const QString &fp) {
        return Utils::FileName::fromString(fp);
    });
}

QVariantMap dBaseProject::toMap() const
{
    QVariantMap result = Project::toMap();
    result[Constants::C_DBASEPROJECT_EXCLUDEDFILES] = m_excludedFiles;
    return result;
}

Project::RestoreResult dBaseProject::fromMap(const QVariantMap &map, QString *errorMessage)
{
    m_excludedFiles = map.value(Constants::C_DBASEPROJECT_EXCLUDEDFILES).toStringList();
    return Project::fromMap(map, errorMessage);
}

}  // namespace: dBase
