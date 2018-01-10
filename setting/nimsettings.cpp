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

#include "nimsettings.h"
#include "nimcodestylepreferencesfactory.h"

#include "../plugins/dbasepluginconstants.h"

#include <texteditor/icodestylepreferencesfactory.h>
#include <texteditor/texteditorsettings.h>
#include <texteditor/codestylepool.h>
#include <texteditor/simplecodestylepreferences.h>
#include <texteditor/tabsettings.h>
#include <coreplugin/icore.h>

using namespace TextEditor;

namespace dBase {

SimpleCodeStylePreferences *m_globalCodeStyle = nullptr;

dBaseSettings::dBaseSettings(QObject *parent)
    : QObject(parent)
{
    // code style factory
    auto factory = new dBaseCodeStylePreferencesFactory();
    TextEditorSettings::registerCodeStyleFactory(factory);

    // code style pool
    auto pool = new CodeStylePool(factory, this);
    TextEditorSettings::registerCodeStylePool(dBase::Constants::C_DBASELANGUAGE_ID, pool);

    m_globalCodeStyle = new SimpleCodeStylePreferences();
    m_globalCodeStyle->setDelegatingPool(pool);
    m_globalCodeStyle->setDisplayName(tr("Global", "Settings"));
    m_globalCodeStyle->setId(dBase::Constants::C_DBASEGLOBALCODESTYLE_ID);
    pool->addCodeStyle(m_globalCodeStyle);
    TextEditorSettings::registerCodeStyle(dBase::Constants::C_DBASELANGUAGE_ID, m_globalCodeStyle);

    auto dbaseCodeStyle = new SimpleCodeStylePreferences();
    dbaseCodeStyle->setId("dbase");
    dbaseCodeStyle->setDisplayName(tr("dBase"));
    dbaseCodeStyle->setReadOnly(true);
    TabSettings dbaseTabSettings;
    dbaseTabSettings.m_tabPolicy = TabSettings::SpacesOnlyTabPolicy;
    dbaseTabSettings.m_tabSize = 2;
    dbaseTabSettings.m_indentSize = 2;
    dbaseTabSettings.m_continuationAlignBehavior = TabSettings::ContinuationAlignWithIndent;
    dbaseCodeStyle->setTabSettings(dbaseTabSettings);
    pool->addCodeStyle(dbaseCodeStyle);

    m_globalCodeStyle->setCurrentDelegate(dbaseCodeStyle);

    pool->loadCustomCodeStyles();

    // load global settings (after built-in settings are added to the pool)
    QSettings *s = Core::ICore::settings();
    m_globalCodeStyle->fromSettings(QLatin1String(dBase::Constants::C_DBASELANGUAGE_ID), s);

    TextEditorSettings::registerMimeTypeForLanguageId(dBase::Constants::C_DBASE_MIMETYPE, dBase::Constants::C_DBASELANGUAGE_ID);
    TextEditorSettings::registerMimeTypeForLanguageId(dBase::Constants::C_DBASE_SCRIPT_MIMETYPE, dBase::Constants::C_DBASELANGUAGE_ID);
}

dBaseSettings::~dBaseSettings()
{
    TextEditorSettings::unregisterCodeStyle(dBase::Constants::C_DBASELANGUAGE_ID);
    TextEditorSettings::unregisterCodeStylePool(dBase::Constants::C_DBASELANGUAGE_ID);
    TextEditorSettings::unregisterCodeStyleFactory(dBase::Constants::C_DBASELANGUAGE_ID);

    delete m_globalCodeStyle;
    m_globalCodeStyle = nullptr;
}

SimpleCodeStylePreferences *dBaseSettings::globalCodeStyle()
{
    return m_globalCodeStyle;
}

} // namespace: dBase
