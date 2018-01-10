#include "dbasehighlighter.h"

#include <texteditor/textdocument.h>
#include <texteditor/texteditorconstants.h>

#include <utils/qtcassert.h>

namespace dBase {

dBaseHighlighter::dBaseHighlighter(){
    setDefaultTextFormatCategories();
}

void dBaseHighlighter::highlightBlock(const QString &text)
{
    Q_UNUSED(text)
//  setCurrentBlockState(highlightLine(text,previousBlockState()));
    setCurrentBlockState(previousBlockState());
}

int dBaseHighlighter::highlightLine(const QString &text, int initialState)
{
    Q_UNUSED(text)
    Q_UNUSED(initialState)
    
    return 1;
}

}  // namespace: dBase
