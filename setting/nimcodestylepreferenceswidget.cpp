/****************************************************************************
**
** Copyright (C) Filippo Cucchetto <filippocucchetto@gmail.com>
** Contact: http://www.qt.io/licensing
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#include "nimcodestylepreferenceswidget.h"
#include "ui_nimcodestylepreferenceswidget.h"

#include "../plugins/dbasepluginconstants.h"
#include "../editor/dbaseeditorfactory.h"

#include <extensionsystem/pluginmanager.h>
#include <texteditor/displaysettings.h>
#include <texteditor/fontsettings.h>
#include <texteditor/icodestylepreferences.h>
#include <texteditor/indenter.h>
#include <texteditor/tabsettings.h>
#include <texteditor/textdocument.h>
#include <texteditor/texteditorsettings.h>
#include <texteditor/snippets/snippetprovider.h>

using namespace TextEditor;

namespace dBase {

dBaseCodeStylePreferencesWidget::dBaseCodeStylePreferencesWidget(ICodeStylePreferences *preferences, QWidget *parent)
    : QWidget(parent)
    , m_preferences(preferences)
    , m_ui(new Ui::dBaseCodeStylePreferencesWidget())
{
    m_ui->setupUi(this);
    m_ui->tabPreferencesWidget->setPreferences(preferences);
    m_ui->previewTextEdit->setPlainText(dBase::Constants::C_DBASECODESTYLEPREVIEWSNIPPET);

    decorateEditor(TextEditorSettings::fontSettings());
    connect(TextEditorSettings::instance(), &TextEditorSettings::fontSettingsChanged,
       this, &dBaseCodeStylePreferencesWidget::decorateEditor);

    connect(m_preferences, &ICodeStylePreferences::currentTabSettingsChanged,
            this, &dBaseCodeStylePreferencesWidget::updatePreview);

    setVisualizeWhitespace(true);

    updatePreview();
}

dBaseCodeStylePreferencesWidget::~dBaseCodeStylePreferencesWidget()
{
    delete m_ui;
    m_ui = nullptr;
}

void dBaseCodeStylePreferencesWidget::decorateEditor(const FontSettings &fontSettings)
{
    m_ui->previewTextEdit->textDocument()->setFontSettings(fontSettings);
    dBaseEditorFactory::decorateEditor(m_ui->previewTextEdit);
}

void dBaseCodeStylePreferencesWidget::setVisualizeWhitespace(bool on)
{
    DisplaySettings displaySettings = m_ui->previewTextEdit->displaySettings();
    displaySettings.m_visualizeWhitespace = on;
    m_ui->previewTextEdit->setDisplaySettings(displaySettings);
}

void dBaseCodeStylePreferencesWidget::updatePreview()
{
    QTextDocument *doc = m_ui->previewTextEdit->document();

    const TabSettings &ts = m_preferences
            ? m_preferences->currentTabSettings()
            : TextEditorSettings::codeStyle()->tabSettings();
    m_ui->previewTextEdit->textDocument()->setTabSettings(ts);

    QTextBlock block = doc->firstBlock();
    QTextCursor tc = m_ui->previewTextEdit->textCursor();
    tc.beginEditBlock();
    while (block.isValid()) {
        m_ui->previewTextEdit->textDocument()->indenter()
                ->indentBlock(doc, block, QChar::Null, ts);
        block = block.next();
    }
    tc.endEditBlock();
}

} // namespace: dBase

