#ifndef DBASECOMPILERBUILDSTEPCONFIGWIDGET_H_
#define DBASECOMPILERBUILDSTEPCONFIGWIDGET_H_
#pragma once

#include <projectexplorer/buildstep.h>

namespace dBase {

class dBaseCompilerBuildStep;

namespace Ui { class dBaseCompilerBuildStepConfigWidget; }

class dBaseCompilerBuildStepConfigWidget : public ProjectExplorer::BuildStepConfigWidget
{
    Q_OBJECT

public:
    dBaseCompilerBuildStepConfigWidget(dBaseCompilerBuildStep *buildStep);
    ~dBaseCompilerBuildStepConfigWidget();

    QString summaryText() const override;
    QString displayName() const override;

private:
    void updateUi();
    void updateCommandLineText();
    void updateTargetComboBox();
    void updateAdditionalArgumentsLineEdit();
    void updateDefaultArgumentsComboBox();

    void onAdditionalArgumentsTextEdited(const QString &text);
    void onTargetChanged(int index);
    void onDefaultArgumentsComboBoxIndexChanged(int index);

    dBaseCompilerBuildStep *m_buildStep;
    QScopedPointer<Ui::dBaseCompilerBuildStepConfigWidget> m_ui;
};

}  // namespace: dBase
#endif
