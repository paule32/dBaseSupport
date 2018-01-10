#ifndef DBASEEDITORFACTORY_H_
#define DBASEEDITORFACTORY_H_
#pragma once
#include <texteditor/texteditor.h>

namespace dBase {

class dBaseEditorFactory :
    public TextEditor::TextEditorFactory
{
    Q_OBJECT
public:
    dBaseEditorFactory();
    
    Core::IEditor *createEditor() override;
    static void decorateEditor(TextEditor::TextEditorWidget *editor);
};

}  // namespace: dBase
#endif
