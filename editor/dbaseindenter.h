#ifndef DBASEINDENTER_H_
#define DBASEINDENTER_H_
#pragma once

#include <texteditor/indenter.h>

namespace TextEditor { class SimpleCodeStylePreferences; }
namespace dBase {

class dBaseIndenter : public TextEditor::Indenter {
public:
    dBaseIndenter();
};

}
#endif
