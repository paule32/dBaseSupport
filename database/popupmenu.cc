#include "popupmenu.h"

#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QPalette>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

PopupMenu::PopupMenu(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Popup Menu"));
    resize(32, 32);
     
    setColor(210,120,210);
}

void PopupMenu::setColor(int r, int g, int b)
{
    color_.setRed(r);
    color_.setGreen(g);
    color_.setBlue(b);
}

void PopupMenu::setColor(const QColor &col) {
    setColor(col.red(),col.green(),col.blue());
}

void PopupMenu::resizeEvent(QResizeEvent *evt)
{
    Q_UNUSED(evt);
    resize(32,32);
}

void PopupMenu::paintEvent(QPaintEvent *evt)
{
    Q_UNUSED(evt);

    QPixmap pixmap(":/img/dbsql.png");
    pixmap.scaled(32,32);
    
    QPainter painter(this);
    painter.drawPixmap(0,0,32,32,pixmap);
    painter.end();
}



