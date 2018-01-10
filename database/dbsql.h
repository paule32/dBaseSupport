#ifndef DBSQL_H
#define DBSQL_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QResizeEvent>

#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT dbSQL : public QWidget
{
    Q_OBJECT
    
public:
    explicit dbSQL(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *evt);
    void resizeEvent(QResizeEvent *evt);
};

#endif
