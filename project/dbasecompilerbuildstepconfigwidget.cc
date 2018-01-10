#include "dbasecompilerbuildstepconfigwidget.h"
#include "ui_dbasecompilerbuildstepconfigwidget.h"
#include "dbasebuildconfiguration.h"
#include "dbasecompilerbuildstep.h"
#include "dbaseproject.h"

#include "../plugins/dbasepluginconstants.h"

#include <utils/qtcassert.h>

using namespace ProjectExplorer;
using namespace Utils;

namespace dBase {

dBaseCompilerBuildStepConfigWidget::dBaseCompilerBuildStepConfigWidget(dBaseCompilerBuildStep *buildStep)
    : BuildStepConfigWidget()
    , m_buildStep(buildStep)
    , m_ui(new Ui::dBaseCompilerBuildStepConfigWidget())
{
    m_ui->setupUi(this);

    // Connect the project signals
    auto project = static_cast<dBaseProject *>(m_buildStep->project());
    connect(project, &dBaseProject::fileListChanged,
            this, &dBaseCompilerBuildStepConfigWidget::updateUi);

    // Connect build step signals
    connect(m_buildStep, &dBaseCompilerBuildStep::processParametersChanged,
            this, &dBaseCompilerBuildStepConfigWidget::updateUi);

    // Connect UI signals
    connect(m_ui->targetComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
            this, &dBaseCompilerBuildStepConfigWidget::onTargetChanged);
    connect(m_ui->additionalArgumentsLineEdit, &QLineEdit::textEdited,
            this, &dBaseCompilerBuildStepConfigWidget::onAdditionalArgumentsTextEdited);
    connect(m_ui->defaultArgumentsComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
            this, &dBaseCompilerBuildStepConfigWidget::onDefaultArgumentsComboBoxIndexChanged);

    updateUi();
}

dBaseCompilerBuildStepConfigWidget::~dBaseCompilerBuildStepConfigWidget() = default;

QString dBaseCompilerBuildStepConfigWidget::summaryText() const
{
    return tr(Constants::C_DBASECOMPILERBUILDSTEPWIDGET_SUMMARY);
}

QString dBaseCompilerBuildStepConfigWidget::displayName() const
{
    return tr(Constants::C_DBASECOMPILERBUILDSTEPWIDGET_DISPLAY);
}

void dBaseCompilerBuildStepConfigWidget::onTargetChanged(int index)
{
    Q_UNUSED(index);
    auto data = m_ui->targetComboBox->currentData();
    FileName path = FileName::fromString(data.toString());
    m_buildStep->setTargetdBaseFile(path);
}

void dBaseCompilerBuildStepConfigWidget::onDefaultArgumentsComboBoxIndexChanged(int index)
{
    auto options = static_cast<dBaseCompilerBuildStep::DefaultBuildOptions>(index);
    m_buildStep->setDefaultCompilerOptions(options);
}

void dBaseCompilerBuildStepConfigWidget::updateUi()
{
    updateCommandLineText();
    updateTargetComboBox();
    updateAdditionalArgumentsLineEdit();
    updateDefaultArgumentsComboBox();
}

void dBaseCompilerBuildStepConfigWidget::onAdditionalArgumentsTextEdited(const QString &text)
{
    m_buildStep->setUserCompilerOptions(text.split(QChar::Space));
}

void dBaseCompilerBuildStepConfigWidget::updateCommandLineText()
{
    ProcessParameters *parameters = m_buildStep->processParameters();

    QStringList command;
    command << parameters->command();
    command << parameters->arguments();

    // Remove empty args
    auto predicate = [](const QString & str) { return str.isEmpty(); };
    auto it = std::remove_if(command.begin(), command.end(), predicate);
    command.erase(it, command.end());

    m_ui->commandTextEdit->setText(command.join(QChar::LineFeed));
}

void dBaseCompilerBuildStepConfigWidget::updateTargetComboBox()
{
    QTC_ASSERT(m_buildStep, return);

    auto project = qobject_cast<dBaseProject *>(m_buildStep->project());
    QTC_ASSERT(project, return);

    // Re enter the files
    m_ui->targetComboBox->clear();
    foreach (const FileName &file, project->dbaseFiles())
        m_ui->targetComboBox->addItem(file.fileName(), file.toString());

    const int index = m_ui->targetComboBox->findData(m_buildStep->targetdBaseFile().toString());
    m_ui->targetComboBox->setCurrentIndex(index);
}

void dBaseCompilerBuildStepConfigWidget::updateAdditionalArgumentsLineEdit()
{
    const QString text = m_buildStep->userCompilerOptions().join(QChar::Space);
    m_ui->additionalArgumentsLineEdit->setText(text);
}

void dBaseCompilerBuildStepConfigWidget::updateDefaultArgumentsComboBox()
{
    const int index = m_buildStep->defaultCompilerOptions();
    m_ui->defaultArgumentsComboBox->setCurrentIndex(index);
}

}  // namespace: dBase
