#include "dbaserunconfigurationwidget.h"
#include "dbaserunconfiguration.h"

#include <projectexplorer/runconfigurationaspects.h>

#include <QFormLayout>

using namespace ProjectExplorer;

namespace dBase {

dBaseRunConfigurationWidget::dBaseRunConfigurationWidget(
      dBaseRunConfiguration *rc,
      QWidget *parent)
    : QWidget (parent)
    , m_rc(rc)
{
    QTC_ASSERT(rc, return);
    auto fl = new QFormLayout(this);
    fl->setMargin(0);
    fl->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    rc->extraAspect<ArgumentsAspect>()->addToMainConfigurationWidget(this, fl);
    rc->extraAspect<TerminalAspect>()->addToMainConfigurationWidget(this,fl);
}

} // namespace Nim
