#include "dbaseprojectnode.h"
#include "dbaseproject.h"

using namespace ProjectExplorer;
using namespace Utils;

namespace dBase {
dBaseProjectNode::dBaseProjectNode(dBaseProject &project, const FileName &projectFilePath)
    : ProjectNode(projectFilePath)
    , m_project(project)
{}

bool dBaseProjectNode::supportsAction(ProjectAction action, const Node *node) const
{
    switch (node->nodeType()) {
    case NodeType::File:
        return action == ProjectAction::Rename
            || action == ProjectAction::RemoveFile;
    case NodeType::Folder:
    case NodeType::Project:
        return action == ProjectAction::AddNewFile
            || action == ProjectAction::RemoveFile
            || action == ProjectAction::AddExistingFile;
    default:
        return ProjectNode::supportsAction(action, node);
    }
}

bool dBaseProjectNode::addFiles(const QStringList &filePaths, QStringList *notAdded)
{
    Q_UNUSED(notAdded)
    return m_project.addFiles(filePaths);
}

bool dBaseProjectNode::removeFiles(const QStringList &filePaths, QStringList *notRemoved)
{
    Q_UNUSED(notRemoved)
    return m_project.removeFiles(filePaths);
}

bool dBaseProjectNode::deleteFiles(const QStringList &)
{
    return true;
}

bool dBaseProjectNode::renameFile(const QString &filePath, const QString &newFilePath)
{
    return m_project.renameFile(filePath, newFilePath);
}

}  // namespace dBase
