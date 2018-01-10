#include "dbaserunconfigurationfactory.h"
#include "dbaseproject.h"
#include "dbaserunconfiguration.h"

#include "../plugins/dbasepluginconstants.h"

#include <debugger/debuggerrunconfigurationaspect.h>
#include <projectexplorer/target.h>

#include <memory>

using namespace ProjectExplorer;

namespace dBase {
dBaseRunConfigurationFactory::dBaseRunConfigurationFactory()
{}

QList<Core::Id> dBaseRunConfigurationFactory::availableCreationIds(
    Target *parent,
    IRunConfigurationFactory::CreationMode mode) const
{
    Q_UNUSED(mode)
    QList<Core::Id> result;
    
    if (canHandle(parent))
    result.append(Constants::C_DBASERUNCONFIGURATION_ID);
    return result;
}

QString dBaseRunConfigurationFactory::displayNameForId(Core::Id id) const {
    return id.toString() + QStringLiteral("-TempRunConf");
}

bool dBaseRunConfigurationFactory::canCreate(Target *parent, Core::Id id) const
{
    Q_UNUSED(id)
    return canHandle(parent);
}

bool dBaseRunConfigurationFactory::canRestore(Target *parent, const QVariantMap &map) const
{
    Q_UNUSED(parent)
    Q_UNUSED(map)
    return canHandle(parent);
}

bool dBaseRunConfigurationFactory::canClone(Target *parent, RunConfiguration *product) const
{
    QTC_ASSERT(parent , return false);
    QTC_ASSERT(product, return false);
    
    return canHandle(parent);
}

     RunConfiguration *
dBaseRunConfigurationFactory::clone(Target *parent, RunConfiguration *product)
{
    QTC_ASSERT(parent , return nullptr);
    QTC_ASSERT(product, return nullptr);
    
    std::unique_ptr<dBaseRunConfiguration> result(
    createHelper<dBaseRunConfiguration>(parent,
    Constants::C_DBASERUNCONFIGURATION_ID));
    return result->fromMap(product->toMap()) ? result.release() : nullptr;
}

bool dBaseRunConfigurationFactory::canHandle(Target *parent) const
{
    Q_UNUSED(parent)
    if (!parent->project()->supportsKit(parent->kit()))
    return false;
    return qobject_cast<dBaseProject *>(parent->project());
}

     RunConfiguration *
dBaseRunConfigurationFactory::doCreate(Target *parent, Core::Id id)
{
    return createHelper<dBaseRunConfiguration>(parent, id);
}

     RunConfiguration *
dBaseRunConfigurationFactory::doRestore(Target *parent, const QVariantMap &map)
{
    Q_UNUSED(map)
    auto result = createHelper<dBaseRunConfiguration>(parent, idFromMap(map));
    return result;
}

}  // namespace: dBase
