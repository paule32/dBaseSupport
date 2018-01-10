#ifndef DBASECOMPILERCLEANSTEPCONFIGWIDGET_H_
#define DBASECOMPILERCLEANSTEPCONFIGWIDGET_H_
#pragma once

#include <projectexplorer/buildstep.h>

namespace dBase {

class dBaseCompilerCleanStep;

namespace Ui { class dBaseCompilerCleanStepConfigWidget; }

class dBaseCompilerCleanStepConfigWidget : public ProjectExplorer::BuildStepConfigWidget
{
    Q_OBJECT

public:
    dBaseCompilerCleanStepConfigWidget(dBaseCompilerCleanStep *cleanStep);

    ~dBaseCompilerCleanStepConfigWidget();

    QString summaryText() const override;
    QString displayName() const override;

private:
    void updateUi();

    dBaseCompilerCleanStep *m_cleanStep;
    QScopedPointer<Ui::dBaseCompilerCleanStepConfigWidget> m_ui;
};

}  // namespace: dBase
#endif
