/****************************************************************************
**
** Copyright (C) Filippo Cucchetto <filippocucchetto@gmail.com>
** Contact: http://www.qt.io/licensing
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#include "dbasecompilerbuildstep.h"
#include "dbasebuildconfiguration.h"
#include "dbasecompilerbuildstepconfigwidget.h"
#include "dbaseproject.h"
#include "dbasetoolchain.h"

#include "../plugins/dbasepluginconstants.h"

#include <projectexplorer/projectexplorerconstants.h>
#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/kitinformation.h>
#include <projectexplorer/ioutputparser.h>
#include <utils/qtcassert.h>

#include <QDir>
#include <QRegularExpression>

using namespace ProjectExplorer;
using namespace Utils;

namespace dBase {

class dBaseParser : public ProjectExplorer::IOutputParser
{
public:
    void stdOutput(const QString &line) final
    {
        parseLine(line.trimmed());
        IOutputParser::stdOutput(line);
    }

    void stdError(const QString &line) final
    {
        parseLine(line.trimmed());
        IOutputParser::stdError(line);
    }

private:
    void parseLine(const QString &line)
    {
        static QRegularExpression regex("(.+.prg)\\((\\d+), (\\d+)\\) (.+)",
                                        QRegularExpression::OptimizeOnFirstUsageOption);
        static QRegularExpression warning("(Warning):(.*)",
                                          QRegularExpression::OptimizeOnFirstUsageOption);
        static QRegularExpression error("(Error):(.*)",
                                        QRegularExpression::OptimizeOnFirstUsageOption);

        QRegularExpressionMatch match = regex.match(line);
        if (!match.hasMatch())
            return;
        const QString filename = match.captured(1);
        bool lineOk = false;
        const int lineNumber = match.captured(2).toInt(&lineOk);
        const QString message = match.captured(4);
        if (!lineOk)
            return;

        Task::TaskType type = Task::Unknown;

        if (warning.match(message).hasMatch())
            type = Task::Warning;
        else if (error.match(message).hasMatch())
            type = Task::Error;
        else
            return;

        Task task(type,
                  message,
                  Utils::FileName::fromUserInput(filename),
                  lineNumber,
                  ProjectExplorer::Constants::TASK_CATEGORY_COMPILE);
        emit addTask(task);
    }
};

dBaseCompilerBuildStep::dBaseCompilerBuildStep(BuildStepList *parentList)
    : AbstractProcessStep(parentList, Constants::C_DBASECOMPILERBUILDSTEP_ID)
{
    setDefaultDisplayName(tr(Constants::C_DBASECOMPILERBUILDSTEP_DISPLAY));
    setDisplayName(tr(Constants::C_DBASECOMPILERBUILDSTEP_DISPLAY));

    auto bc = qobject_cast<dBaseBuildConfiguration *>(buildConfiguration());
    connect(bc, &dBaseBuildConfiguration::buildDirectoryChanged,
            this, &dBaseCompilerBuildStep::updateProcessParameters);
    connect(this, &dBaseCompilerBuildStep::outFilePathChanged,
            bc, &dBaseBuildConfiguration::outFilePathChanged);
    connect(bc->target()->project(), &ProjectExplorer::Project::fileListChanged,
            this, &dBaseCompilerBuildStep::updateTargetdBaseFile);
    updateProcessParameters();
}

bool dBaseCompilerBuildStep::init(QList<const BuildStep *> &earlierSteps)
{
    setOutputParser(new dBaseParser());
    if (IOutputParser *parser = target()->kit()->createOutputParser())
        appendOutputParser(parser);
    outputParser()->setWorkingDirectory(processParameters()->effectiveWorkingDirectory());
    return AbstractProcessStep::init(earlierSteps);
}

BuildStepConfigWidget *dBaseCompilerBuildStep::createConfigWidget()
{
    return new dBaseCompilerBuildStepConfigWidget(this);
}

bool dBaseCompilerBuildStep::fromMap(const QVariantMap &map)
{
    AbstractProcessStep::fromMap(map);
    m_userCompilerOptions = map[Constants::C_DBASECOMPILERBUILDSTEP_USERCOMPILEROPTIONS].toString().split('|');
    m_defaultOptions = static_cast<DefaultBuildOptions>(map[Constants::C_DBASECOMPILERBUILDSTEP_DEFAULTBUILDOPTIONS].toInt());
    m_targetdBaseFile = FileName::fromString(map[Constants::C_DBASECOMPILERBUILDSTEP_TARGETDBASEFILE].toString());
    updateProcessParameters();
    return true;
}

QVariantMap dBaseCompilerBuildStep::toMap() const
{
    QVariantMap result = AbstractProcessStep::toMap();
    result[Constants::C_DBASECOMPILERBUILDSTEP_USERCOMPILEROPTIONS] = m_userCompilerOptions.join('|');
    result[Constants::C_DBASECOMPILERBUILDSTEP_DEFAULTBUILDOPTIONS] = m_defaultOptions;
    result[Constants::C_DBASECOMPILERBUILDSTEP_TARGETDBASEFILE] = m_targetdBaseFile.toString();
    return result;
}

QStringList dBaseCompilerBuildStep::userCompilerOptions() const
{
    return m_userCompilerOptions;
}

void dBaseCompilerBuildStep::setUserCompilerOptions(const QStringList &options)
{
    m_userCompilerOptions = options;
    emit userCompilerOptionsChanged(options);
    updateProcessParameters();
}

dBaseCompilerBuildStep::DefaultBuildOptions dBaseCompilerBuildStep::defaultCompilerOptions() const
{
    return m_defaultOptions;
}

void dBaseCompilerBuildStep::setDefaultCompilerOptions(dBaseCompilerBuildStep::DefaultBuildOptions options)
{
    if (m_defaultOptions == options)
        return;
    m_defaultOptions = options;
    emit defaultCompilerOptionsChanged(options);
    updateProcessParameters();
}

FileName dBaseCompilerBuildStep::targetdBaseFile() const
{
    return m_targetdBaseFile;
}

void dBaseCompilerBuildStep::setTargetdBaseFile(const FileName &targetdBaseFile)
{
    if (targetdBaseFile == m_targetdBaseFile)
        return;
    m_targetdBaseFile = targetdBaseFile;
    emit targetdBaseFileChanged(targetdBaseFile);
    updateProcessParameters();
}

FileName dBaseCompilerBuildStep::outFilePath() const
{
    return m_outFilePath;
}

void dBaseCompilerBuildStep::setOutFilePath(const FileName &outFilePath)
{
    if (outFilePath == m_outFilePath)
        return;
    m_outFilePath = outFilePath;
    emit outFilePathChanged(outFilePath);
}

void dBaseCompilerBuildStep::updateProcessParameters()
{
    updateOutFilePath();
    updateCommand();
    updateArguments();
    updateWorkingDirectory();
    updateEnvironment();
    emit processParametersChanged();
}

void dBaseCompilerBuildStep::updateOutFilePath()
{
    auto bc = qobject_cast<dBaseBuildConfiguration *>(buildConfiguration());
    QTC_ASSERT(bc, return);
    const QString targetName = Utils::HostOsInfo::withExecutableSuffix(m_targetdBaseFile.toFileInfo().baseName());
    FileName outFilePath = bc->buildDirectory().appendPath(targetName);
    setOutFilePath(outFilePath);
}

void dBaseCompilerBuildStep::updateCommand()
{
    QTC_ASSERT(target(), return);
    QTC_ASSERT(target()->kit(), return);
    Kit *kit = target()->kit();
    auto tc = dynamic_cast<dBaseToolChain*>(ToolChainKitInformation::toolChain(kit, Constants::C_DBASELANGUAGE_ID));
    QTC_ASSERT(tc, return);
    processParameters()->setCommand(tc->compilerCommand().toString());
}

void dBaseCompilerBuildStep::updateWorkingDirectory()
{
    auto bc = qobject_cast<dBaseBuildConfiguration *>(buildConfiguration());
    QTC_ASSERT(bc, return);
    processParameters()->setWorkingDirectory(bc->buildDirectory().toString());
}

void dBaseCompilerBuildStep::updateArguments()
{
    auto bc = qobject_cast<dBaseBuildConfiguration *>(buildConfiguration());
    QTC_ASSERT(bc, return);

    QStringList arguments;
    arguments << QStringLiteral("c");

    switch (m_defaultOptions) {
    case Release:
        arguments << QStringLiteral("-d:release");
        break;
    case Debug:
        arguments << QStringLiteral("--debugInfo")
                  << QStringLiteral("--lineDir:on");
        break;
    default:
        break;
    }

    arguments << QStringLiteral("--out:%1").arg(m_outFilePath.toString());
    arguments << QStringLiteral("--dbaseCache:%1").arg(bc->cacheDirectory().toString());

    arguments << m_userCompilerOptions;
    arguments << m_targetdBaseFile.toString();

    // Remove empty args
    auto predicate = [](const QString &str) { return str.isEmpty(); };
    auto it = std::remove_if(arguments.begin(), arguments.end(), predicate);
    arguments.erase(it, arguments.end());

    processParameters()->setArguments(arguments.join(QChar::Space));
}

void dBaseCompilerBuildStep::updateEnvironment()
{
    auto bc = qobject_cast<dBaseBuildConfiguration *>(buildConfiguration());
    QTC_ASSERT(bc, return);
    processParameters()->setEnvironment(bc->environment());
}

void dBaseCompilerBuildStep::updateTargetdBaseFile()
{
    if (!m_targetdBaseFile.isEmpty())
        return;
    const Utils::FileNameList dbaseFiles = static_cast<dBaseProject *>(project())->dbaseFiles();
    if (!dbaseFiles.isEmpty())
        setTargetdBaseFile(dbaseFiles.at(0));
}

} // namespace dbase
