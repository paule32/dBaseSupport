#include "dbasetoolchain.h"
#include "dbasetoolchainfactory.h"

#include "../plugins/dbasepluginconstants.h"

#include <projectexplorer/abi.h>
#include <utils/environment.h>

#include <QFileInfo>
#include <QProcess>
#include <QRegExp>

using namespace ProjectExplorer;
using namespace Utils;

namespace dBase {

dBaseToolChain::dBaseToolChain(ToolChain::Detection d)
    : dBaseToolChain(Constants::C_DBASETOOLCHAIN_TYPEID, d)
{}

dBaseToolChain::dBaseToolChain(Core::Id typeId, ToolChain::Detection d)
    : ToolChain(typeId, d)
    , m_compilerCommand(FileName())
    , m_version(std::make_tuple(-1,-1,-1))
{
    setLanguage(Constants::C_DBASELANGUAGE_ID);
}

dBaseToolChain::dBaseToolChain(const dBaseToolChain &other)
    : ToolChain(other.typeId(), other.detection())
    , m_compilerCommand(other.m_compilerCommand)
    , m_version(other.m_version)
{
    setLanguage(Constants::C_DBASELANGUAGE_ID);
}

QString dBaseToolChain::typeDisplayName() const
{
    return dBaseToolChainFactory::tr("dBase");
}

Abi dBaseToolChain::targetAbi() const
{
    return Abi();
}

bool dBaseToolChain::isValid() const
{
    if (m_compilerCommand.isNull())
        return false;
    QFileInfo fi = compilerCommand().toFileInfo();
    return fi.isExecutable();
}

ToolChain::PredefinedMacrosRunner dBaseToolChain::createPredefinedMacrosRunner() const
{
    return ToolChain::PredefinedMacrosRunner();
}

Macros dBaseToolChain::predefinedMacros(const QStringList &) const
{
    return Macros();
}

ToolChain::CompilerFlags dBaseToolChain::compilerFlags(const QStringList &) const
{
    return CompilerFlag::NoFlags;
}

WarningFlags dBaseToolChain::warningFlags(const QStringList &) const
{
    return WarningFlags::NoWarnings;
}

ToolChain::SystemHeaderPathsRunner dBaseToolChain::createSystemHeaderPathsRunner() const
{
    return ToolChain::SystemHeaderPathsRunner();
}

QList<HeaderPath> dBaseToolChain::systemHeaderPaths(const QStringList &, const FileName &) const
{
    return QList<HeaderPath>();
}

void dBaseToolChain::addToEnvironment(Environment &env) const
{
    if (isValid())
        env.prependOrSetPath(compilerCommand().parentDir().toString());
}

QString dBaseToolChain::makeCommand(const Environment &env) const
{
    QString make = "make";
    FileName tmp = env.searchInPath(make);
    return tmp.isEmpty() ? make : tmp.toString();
}

FileName dBaseToolChain::compilerCommand() const
{
    return m_compilerCommand;
}

void dBaseToolChain::setCompilerCommand(const FileName &compilerCommand)
{
    m_compilerCommand = compilerCommand;
    parseVersion(compilerCommand, m_version);
}

IOutputParser *dBaseToolChain::outputParser() const
{
    return nullptr;
}

ToolChainConfigWidget *dBaseToolChain::configurationWidget()
{
    return new dBaseToolChainConfigWidget(this);
}

ToolChain *dBaseToolChain::clone() const
{
    return new dBaseToolChain(*this);
}

QVariantMap dBaseToolChain::toMap() const
{
    QVariantMap data = ToolChain::toMap();
    data[Constants::C_DBASETOOLCHAIN_COMPILER_COMMAND_KEY] = m_compilerCommand.toString();
    return data;
}

QString dBaseToolChain::compilerVersion() const
{
    return m_compilerCommand.isEmpty() || m_version == std::make_tuple(-1,-1,-1)
            ? QString()
            : QString::asprintf("%d.%d.%d",
                                std::get<0>(m_version),
                                std::get<1>(m_version),
                                std::get<2>(m_version));
}

bool dBaseToolChain::fromMap(const QVariantMap &data)
{
    if (!ToolChain::fromMap(data))
        return false;
    setCompilerCommand(FileName::fromString(data.value(Constants::C_DBASETOOLCHAIN_COMPILER_COMMAND_KEY).toString()));
    return true;
}

bool dBaseToolChain::parseVersion(const FileName &path, std::tuple<int, int, int> &result)
{
    QProcess process;
    process.setReadChannel(QProcess::StandardError);
    process.start(path.toString(), {"--version"});
    if (!process.waitForFinished())
        return false;
    const QString version = QString::fromUtf8(process.readLine());
    if (version.isEmpty())
        return false;
    const QRegExp regex("(\\d+)\\.(\\d+)\\.(\\d+)");
    if (regex.indexIn(version) == -1)
        return false;
    const QStringList text = regex.capturedTexts();
    if (text.length() != 4)
        return false;
    result = std::make_tuple(text[1].toInt(), text[2].toInt(), text[3].toInt());
    return true;
};

}  // namespace: dBase
