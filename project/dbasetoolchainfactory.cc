#include "dbasetoolchainfactory.h"
#include "dbasetoolchain.h"

#include "../plugins/dbasepluginconstants.h"

#include <utils/algorithm.h>
#include <utils/environment.h>
#include <utils/pathchooser.h>

#include <QFormLayout>
#include <QProcess>

using namespace ProjectExplorer;
using namespace Utils;

namespace dBase {

dBaseToolChainFactory::dBaseToolChainFactory()
{
    setDisplayName("dBase");
}

bool dBaseToolChainFactory::canCreate()
{
    return true;
}

ToolChain *dBaseToolChainFactory::create(Core::Id l)
{
    if (l != Constants::C_DBASELANGUAGE_ID)
        return nullptr;
    auto result = new dBaseToolChain(ToolChain::ManualDetection);
    result->setLanguage(l);
    return result;
}

bool dBaseToolChainFactory::canRestore(const QVariantMap &data)
{
    return typeIdFromMap(data) == Constants::C_DBASETOOLCHAIN_TYPEID;
}

ToolChain *dBaseToolChainFactory::restore(const QVariantMap &data)
{
    auto tc = new dBaseToolChain(ToolChain::AutoDetection);
    if (tc->fromMap(data))
        return tc;
    delete tc;
    return nullptr;
}

QSet<Core::Id> dBaseToolChainFactory::supportedLanguages() const
{
    return {Constants::C_DBASELANGUAGE_ID};
}

QList<ToolChain *> dBaseToolChainFactory::autoDetect(const QList<ToolChain *> &alreadyKnown)
{
    QList<ToolChain *> result;

    Environment systemEnvironment = Environment::systemEnvironment();
    const FileName compilerPath = systemEnvironment.searchInPath("dbase");
    if (compilerPath.isEmpty())
        return result;

    result = Utils::filtered(alreadyKnown, [compilerPath](ToolChain *tc) {
        return tc->typeId() == Constants::C_DBASETOOLCHAIN_TYPEID
                && tc->compilerCommand() == compilerPath;
    });

    if (!result.empty())
        return result;

    auto tc = new dBaseToolChain(ToolChain::AutoDetection);
    tc->setCompilerCommand(compilerPath);
    result.append(tc);
    return result;
}

QList<ToolChain *> dBaseToolChainFactory::autoDetect(const FileName &compilerPath, const Core::Id &language)
{
    QList<ToolChain *> result;
    if (language == Constants::C_DBASELANGUAGE_ID) {
        auto tc = new dBaseToolChain(ToolChain::ManualDetection);
        tc->setCompilerCommand(compilerPath);
        result.append(tc);
    }
    return result;
}

dBaseToolChainConfigWidget::dBaseToolChainConfigWidget(dBaseToolChain *tc)
    : ToolChainConfigWidget(tc)
    , m_compilerCommand(new PathChooser)
    , m_compilerVersion(new QLineEdit)
{
    // Create ui
    const auto gnuVersionArgs = QStringList("--version");
    m_compilerCommand->setExpectedKind(PathChooser::ExistingCommand);
    m_compilerCommand->setCommandVersionArguments(gnuVersionArgs);
    m_mainLayout->addRow(tr("&Compiler path:"), m_compilerCommand);
    m_compilerVersion->setReadOnly(true);
    m_mainLayout->addRow(tr("&Compiler version:"), m_compilerVersion);

    // Fill
    fillUI();

    // Connect
    connect(m_compilerCommand, &PathChooser::pathChanged, this, &dBaseToolChainConfigWidget::onCompilerCommandChanged);
}

void dBaseToolChainConfigWidget::applyImpl()
{
    auto tc = static_cast<dBaseToolChain *>(toolChain());
    Q_ASSERT(tc);
    if (tc->isAutoDetected())
        return;
    tc->setCompilerCommand(m_compilerCommand->fileName());
}

void dBaseToolChainConfigWidget::discardImpl()
{
    fillUI();
}

bool dBaseToolChainConfigWidget::isDirtyImpl() const
{
    auto tc = static_cast<dBaseToolChain *>(toolChain());
    Q_ASSERT(tc);
    return tc->compilerCommand().toString() != m_compilerCommand->path();
}

void dBaseToolChainConfigWidget::makeReadOnlyImpl()
{
    m_compilerCommand->setReadOnly(true);
}

void dBaseToolChainConfigWidget::fillUI()
{
    auto tc = static_cast<dBaseToolChain *>(toolChain());
    Q_ASSERT(tc);
    m_compilerCommand->setPath(tc->compilerCommand().toString());
    m_compilerVersion->setText(tc->compilerVersion());
}

void dBaseToolChainConfigWidget::onCompilerCommandChanged(const QString &path)
{
    auto tc = static_cast<dBaseToolChain *>(toolChain());
    Q_ASSERT(tc);
    tc->setCompilerCommand(FileName::fromString(path));
    fillUI();
}

}  // namespace: dBase
