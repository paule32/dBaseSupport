#ifndef DBASETOOLCHAIN_H_
#define DBASETOOLCHAIN_H_
#pragma once

#include <projectexplorer/toolchain.h>
#include <projectexplorer/headerpath.h>

namespace dBase {

class dBaseToolChain : public ProjectExplorer::ToolChain
{
public:
    dBaseToolChain(Detection d);
    dBaseToolChain(Core::Id typeId, Detection d);

    QString typeDisplayName() const override;
    ProjectExplorer::Abi targetAbi() const override;
    bool isValid() const override;

    PredefinedMacrosRunner createPredefinedMacrosRunner() const override;
    ProjectExplorer::Macros predefinedMacros(const QStringList &flags) const final;
    CompilerFlags compilerFlags(const QStringList &flags) const final;
    ProjectExplorer::WarningFlags warningFlags(const QStringList &flags) const final;

    SystemHeaderPathsRunner createSystemHeaderPathsRunner() const override;
    QList<ProjectExplorer::HeaderPath> systemHeaderPaths(const QStringList &flags,
                                                         const Utils::FileName &sysRoot) const final;
    void addToEnvironment(Utils::Environment &env) const final;
    QString makeCommand(const Utils::Environment &env) const final;
    Utils::FileName compilerCommand() const final;
    QString compilerVersion() const;
    void setCompilerCommand(const Utils::FileName &compilerCommand);
    ProjectExplorer::IOutputParser *outputParser() const final;
    ProjectExplorer::ToolChainConfigWidget *configurationWidget() final;
    ProjectExplorer::ToolChain *clone() const final;

    QVariantMap toMap() const final;
    bool fromMap(const QVariantMap &data) final;

    static bool parseVersion(const Utils::FileName &path, std::tuple<int, int, int> &version);

private:
    dBaseToolChain(const dBaseToolChain &other);

    Utils::FileName m_compilerCommand;
    std::tuple<int, int, int> m_version;
};

}  // namespace dBase
#endif
