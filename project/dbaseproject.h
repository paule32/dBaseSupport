#ifndef DBASEPROJECT_H_
#define DBASEPROJECT_H_
#pragma once

#include <projectexplorer/project.h>
#include <projectexplorer/projectnodes.h>

#include <QElapsedTimer>
#include <QFutureWatcher>
#include <QTimer>

namespace dBase {
class dBaseProject : public ProjectExplorer::Project {
    Q_OBJECT
public:
    explicit dBaseProject(const Utils::FileName &fileName);
    
    bool needsConfiguration() const override;
    bool supportsKit(ProjectExplorer::Kit *k, QString *errorMessage) const override;
    
    Utils::FileNameList dbaseFiles() const;
    QVariantMap toMap() const override;
    
    bool addFiles(const QStringList &filePaths);
    bool removeFiles(const QStringList &filePaths);
    bool renameFile(const QString &filePath, const QString &newFilePath);

protected:
    RestoreResult fromMap(const QVariantMap &map, QString *errorMessage) override;
    
private:
    void scheduleProjectScan();
    void collectProjectFiles();
    void updateProject();
    
    QStringList m_files;
    QStringList m_excludedFiles;
    
    QFutureWatcher<QList<ProjectExplorer::FileNode *>> m_futureWatcher;
    QElapsedTimer m_lastProjectScan;
    QTimer m_projectScanTimer;
};

}  // namespace: dBase

#endif
