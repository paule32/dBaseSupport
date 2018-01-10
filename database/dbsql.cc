#include "dbsql.h"

#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QPalette>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

dbSQL::dbSQL(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Popup Menu"));
    resize(32, 32);
}
     
void dbSQL::resizeEvent(QResizeEvent *evt)
{
    Q_UNUSED(evt);
    resize(32,32);
}

void dbSQL::paintEvent(QPaintEvent *evt)
{
    Q_UNUSED(evt);

    QPixmap pixmap(":/img/dbsql.png");
    pixmap.scaled(32,32);
    
    QPainter painter(this);
    painter.drawPixmap(0,0,32,32,pixmap);
    painter.end();
}
