#ifndef DBASEHIGHLIGHTER_H_
#define DBASEHIGHLIGHTER_H_
#pragma once
#include <texteditor/syntaxhighlighter.h>

namespace dBase {

class dBaseHighlighter: public TextEditor::SyntaxHighlighter {
    Q_OBJECT
public:
    dBaseHighlighter();
protected:
    void highlightBlock(const QString &text) override;
private:
    int highlightLine(const QString &text, int initialState);
};

}  // namespace: dBase

#endif
