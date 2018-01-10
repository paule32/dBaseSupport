#ifndef DBASETOOLCHAINFACTORY_H_
#define DBASETOOLCHAINFACTORY_H_
#pragma once

#include <projectexplorer/toolchain.h>
#include <projectexplorer/toolchainconfigwidget.h>

namespace Utils { class PathChooser; }
namespace dBase {

class dBaseToolChain;
class dBaseToolChainFactory : public ProjectExplorer::ToolChainFactory
{
    Q_OBJECT
    
public:
    dBaseToolChainFactory();

    bool canCreate() final;
    ProjectExplorer::ToolChain *create(Core::Id l) final;
    bool canRestore(const QVariantMap &data) final;
    ProjectExplorer::ToolChain *restore(const QVariantMap &data) final;
    QSet<Core::Id> supportedLanguages() const final;
    QList<ProjectExplorer::ToolChain *> autoDetect(const QList<ProjectExplorer::ToolChain *> &alreadyKnown) final;
    QList<ProjectExplorer::ToolChain *> autoDetect(const Utils::FileName &compilerPath, const Core::Id &language) final;
};

class dBaseToolChainConfigWidget : public ProjectExplorer::ToolChainConfigWidget
{
    Q_OBJECT

public:
    explicit dBaseToolChainConfigWidget(dBaseToolChain *tc);

protected:
    void applyImpl() final;
    void discardImpl() final;
    bool isDirtyImpl() const final;
    void makeReadOnlyImpl() final;

private:
    void fillUI();
    void onCompilerCommandChanged(const QString &path);

    Utils::PathChooser *m_compilerCommand;
    QLineEdit *m_compilerVersion;
};

}  // namespace: dBase
#endif
