#include "dbasecompilercleanstep.h"
#include "dbasebuildconfiguration.h"
#include "dbasecompilercleanstepconfigwidget.h"

#include "../plugins/dbasepluginconstants.h"

#include <utils/qtcassert.h>

#include <QDir>
#include <QDateTime>

using namespace ProjectExplorer;
using namespace Utils;

namespace dBase {

dBaseCompilerCleanStep::dBaseCompilerCleanStep(BuildStepList *parentList)
    : BuildStep(parentList, Constants::C_DBASECOMPILERCLEANSTEP_ID)
{
    setDefaultDisplayName(tr("dBase Clean Step"));
    setDisplayName(tr("dBase Clean Step"));
}

BuildStepConfigWidget *dBaseCompilerCleanStep::createConfigWidget()
{
    return new dBaseCompilerCleanStepConfigWidget(this);
}

bool dBaseCompilerCleanStep::init(QList<const BuildStep *> &)
{
    FileName buildDir = buildConfiguration()->buildDirectory();
    bool result = buildDir.exists();
    if (result)
        m_buildDir = buildDir;
    return result;
}

void dBaseCompilerCleanStep::run(QFutureInterface<bool> &fi)
{
    if (!m_buildDir.exists()) {
        emit addOutput(tr("Build directory \"%1\" does not exist.").arg(m_buildDir.toUserOutput()), BuildStep::OutputFormat::ErrorMessage);
        reportRunResult(fi, false);
        return;
    }

    if (!removeCacheDirectory()) {
        emit addOutput(tr("Failed to delete the cache directory."), BuildStep::OutputFormat::ErrorMessage);
        reportRunResult(fi, false);
        return;
    }

    if (!removeOutFilePath()) {
        emit addOutput(tr("Failed to delete the out file."), BuildStep::OutputFormat::ErrorMessage);
        reportRunResult(fi, false);
        return;
    }

    emit addOutput(tr("Clean step completed successfully."), BuildStep::OutputFormat::NormalMessage);
    reportRunResult(fi, true);
}

bool dBaseCompilerCleanStep::removeCacheDirectory()
{
    auto bc = qobject_cast<dBaseBuildConfiguration*>(buildConfiguration());
    QTC_ASSERT(bc, return false);
    if (!bc->cacheDirectory().exists())
        return true;
    QDir dir = QDir::fromNativeSeparators(bc->cacheDirectory().toString());
    const QString dirName = dir.dirName();
    if (!dir.cdUp())
        return false;
    const QString newName = QStringLiteral("%1.bkp.%2").arg(dirName, QString::number(QDateTime::currentMSecsSinceEpoch()));
    return dir.rename(dirName, newName);
}

bool dBaseCompilerCleanStep::removeOutFilePath()
{
    auto bc = qobject_cast<dBaseBuildConfiguration*>(buildConfiguration());
    QTC_ASSERT(bc, return false);
    if (!bc->outFilePath().exists())
        return true;
    return QFile(bc->outFilePath().toFileInfo().absoluteFilePath()).remove();
}

}

