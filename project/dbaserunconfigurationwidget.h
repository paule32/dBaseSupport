#ifndef DBASERUNCONFIGURATIONWIDGET_H_
#define DBASERUNCONFIGURATIONWIDGET_H_
#pragma once

#include <QWidget>

namespace dBase {

class dBaseRunConfiguration;
class dBaseRunConfigurationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit dBaseRunConfigurationWidget(dBaseRunConfiguration *rc, QWidget *parent = 0);

private:
    dBaseRunConfiguration* m_rc;
};

} // namespace dBase
#endif
