#include "dbaseeditorfactory.h"
#include "dbaseindenter.h"
#include "dbasehighlighter.h"

#include "../plugins/dbasepluginconstants.h"
#include "../plugins/dbaseplugin.h"

#include <texteditor/texteditoractionhandler.h>
#include <texteditor/texteditorconstants.h>
#include <texteditor/textdocument.h>

#include <utils/qtcassert.h>

using namespace TextEditor;
using namespace Utils;

namespace dBase {

dBaseEditorFactory::dBaseEditorFactory()
{
    setId(Constants::C_DBASEEDITOR_ID);
    setDisplayName(tr(dBase::Constants::C_EDITOR_DISPLAY_NAME));
    
    addMimeType(QLatin1String(dBase::Constants::C_DBASE_MIMETYPE));
    addMimeType(QLatin1String(dBase::Constants::C_DBASE_SCRIPT_MIMETYPE));
    
    setEditorActionHandlers(
    TextEditorActionHandler::Format |
    TextEditorActionHandler::UnCommentSelection |
    TextEditorActionHandler::UnCollapseAll);
    
    setEditorWidgetCreator([]{
        auto result = new TextEditorWidget();
        result->setLanguageSettingsId(dBase::Constants::C_DBASELANGUAGE_ID);
        return result;
    });
    
    setDocumentCreator([]() {
        return new TextDocument(Constants::C_DBASEEDITOR_ID);
    });
    
    setCommentDefinition(CommentDefinition::HashStyle);
    setParenthesesMatchingEnabled(true);
    setMarksVisible(true);
    setCodeFoldingSupported(true);
}

Core::IEditor* dBaseEditorFactory::createEditor()
{
    return TextEditorFactory::createEditor();
}

void dBaseEditorFactory::decorateEditor(TextEditorWidget *editor)
{
    editor->textDocument()->setSyntaxHighlighter(new dBaseHighlighter());
    editor->textDocument()->setIndenter(new dBaseIndenter());
}

}  // namespace: dBase
