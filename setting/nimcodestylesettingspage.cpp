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

#include "nimcodestylesettingspage.h"
#include "nimcodestylepreferencesfactory.h"
#include "nimsettings.h"

#include "../plugins/dbasepluginconstants.h"

#include <extensionsystem/pluginmanager.h>
#include <texteditor/simplecodestylepreferences.h>
#include <texteditor/codestyleeditor.h>
#include <texteditor/texteditorsettings.h>
#include <texteditor/tabsettings.h>
#include <utils/qtcassert.h>

#include <QWidget>

using namespace TextEditor;

namespace dBase {

dBaseCodeStyleSettingsPage::dBaseCodeStyleSettingsPage(QWidget *parent)
    : Core::IOptionsPage(parent)
    , m_dbaseCodeStylePreferences(nullptr)
    , m_widget(nullptr)
{
    setId(dBase::Constants::C_DBASECODESTYLESETTINGSPAGE_ID);
    setDisplayName(tr(dBase::Constants::C_DBASECODESTYLESETTINGSPAGE_DISPLAY));
    setCategory(dBase::Constants::C_DBASECODESTYLESETTINGSPAGE_CATEGORY);
    setDisplayCategory(tr(dBase::Constants::C_DBASECODESTYLESETTINGSPAGE_CATEGORY_DISPLAY));
    setCategoryIcon(Utils::Icon(dBase::Constants::C_DBASE_ICON_PATH));
}

dBaseCodeStyleSettingsPage::~dBaseCodeStyleSettingsPage()
{
    deleteWidget();
}

QWidget *dBaseCodeStyleSettingsPage::widget()
{
    if (!m_widget) {
        auto originalTabPreferences = qobject_cast<SimpleCodeStylePreferences *>(dBaseSettings::globalCodeStyle());
        m_dbaseCodeStylePreferences = new SimpleCodeStylePreferences(m_widget);
        m_dbaseCodeStylePreferences->setDelegatingPool(originalTabPreferences->delegatingPool());
        m_dbaseCodeStylePreferences->setTabSettings(originalTabPreferences->tabSettings());
        m_dbaseCodeStylePreferences->setCurrentDelegate(originalTabPreferences->currentDelegate());
        m_dbaseCodeStylePreferences->setId(originalTabPreferences->id());
        auto factory = TextEditorSettings::codeStyleFactory(dBase::Constants::C_DBASELANGUAGE_ID);
        m_widget = new CodeStyleEditor(factory, m_dbaseCodeStylePreferences);
    }
    return m_widget;
}

void dBaseCodeStyleSettingsPage::apply()
{

}

void dBaseCodeStyleSettingsPage::finish()
{
    deleteWidget();
}

void dBaseCodeStyleSettingsPage::deleteWidget()
{
    if (m_widget) {
        delete m_widget;
        m_widget = nullptr;
    }
}

}
