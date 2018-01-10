#pragma once

#include <texteditor/icodestylepreferencesfactory.h>

namespace dBase {

class dBaseCodeStylePreferencesFactory : public TextEditor::ICodeStylePreferencesFactory
{
    Q_OBJECT

public:
    dBaseCodeStylePreferencesFactory();

    Core::Id languageId();
    QString displayName();
    TextEditor::ICodeStylePreferences *createCodeStyle() const;
    QWidget *createEditor(TextEditor::ICodeStylePreferences *settings,
                          QWidget *parent) const;
    TextEditor::Indenter *createIndenter() const;
    TextEditor::SnippetProvider *snippetProvider() const;
    QString previewText() const;
};

} // namespace: dBase
