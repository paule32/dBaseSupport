#ifndef DBASEBUILDCONFIGURATIONWIDGET_H_
#define DBASEBUILDCONFIGURATIONWIDGET_H_
#pragma once

#include <projectexplorer/namedwidget.h>

QT_BEGIN_NAMESPACE
class QComboBox;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

namespace Utils { class PathChooser; }

namespace dBase {

class dBaseBuildConfiguration;
class dBaseBuildConfigurationWidget : public ProjectExplorer::NamedWidget
{
    Q_OBJECT

public:
    explicit dBaseBuildConfigurationWidget(dBaseBuildConfiguration *bc);
    ~dBaseBuildConfigurationWidget();

private:
    void updateUi();
    void onPathEdited(const QString &path);

    dBaseBuildConfiguration *m_bc;
    Utils::PathChooser *m_buildDirectoryChooser;
};

}  // namespace: dBase
#endif
