#ifndef DBASEPROJECTNODE_H_
#define DBASEPROJECTNODE_H_
#pragma once

#include "dbaseproject.h"
#include <projectexplorer/projectnodes.h>

namespace Utils { class FileName; }
namespace dBase {

class dBaseProject;
class dBaseProjectNode : public ProjectExplorer::ProjectNode
{
public:
    dBaseProjectNode(dBaseProject &project, const Utils::FileName &projectFilePath);
    
    bool supportsAction(ProjectExplorer::ProjectAction action, const Node *node) const override;
    bool addFiles(const QStringList &filePaths, QStringList *notAdded) override;
    bool removeFiles(const QStringList &filePaths, QStringList *notRemoved) override;
    bool deleteFiles(const QStringList &filePaths) override;
    bool renameFile(const QString &filePath, const QString &newFilePath) override;
    
private:
    dBaseProject &m_project;
};

}  // namespace: dBase

#endif  // DBASEPROJECTNODE_H_
