#include "nimcodestylepreferencesfactory.h"
#include "nimcodestylepreferenceswidget.h"

#include "../plugins/dbasepluginconstants.h"
#include "../editor/dbaseindenter.h"

#include <coreplugin/id.h>
#include <texteditor/simplecodestylepreferences.h>
#include <texteditor/snippets/snippetprovider.h>

#include <extensionsystem/pluginmanager.h>

#include <QWidget>
#include <QLayout>

namespace dBase {

dBaseCodeStylePreferencesFactory::dBaseCodeStylePreferencesFactory()
{
}

Core::Id dBaseCodeStylePreferencesFactory::languageId()
{
    return Constants::C_DBASELANGUAGE_ID;
}

QString dBaseCodeStylePreferencesFactory::displayName()
{
    return tr(Constants::C_DBASELANGUAGE_NAME);
}

TextEditor::ICodeStylePreferences *dBaseCodeStylePreferencesFactory::createCodeStyle() const
{
    return new TextEditor::SimpleCodeStylePreferences();
}

QWidget *dBaseCodeStylePreferencesFactory::createEditor(TextEditor::ICodeStylePreferences *preferences,
                                                      QWidget *parent) const
{
    auto result = new dBaseCodeStylePreferencesWidget(preferences, parent);
    result->layout()->setMargin(0);
    return result;
}

TextEditor::Indenter *dBaseCodeStylePreferencesFactory::createIndenter() const
{
    return new dBaseIndenter();
}

TextEditor::SnippetProvider *dBaseCodeStylePreferencesFactory::snippetProvider() const
{
    return ExtensionSystem::PluginManager::getObject<TextEditor::SnippetProvider>(
        [](TextEditor::SnippetProvider *provider) {
            return provider->groupId() == Constants::C_DBASESNIPPETGROUP_ID;
        });
}

QString dBaseCodeStylePreferencesFactory::previewText() const
{
    return QLatin1String(dBase::Constants::C_DBASECODESTYLEPREVIEWSNIPPET);
}

}
