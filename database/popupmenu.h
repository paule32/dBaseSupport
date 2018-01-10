#ifndef POPUPMENU_H
#define POPUPMENU_H

#include <QTime>
#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QResizeEvent>

#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT PopupMenu : public QWidget
{
    Q_OBJECT
    
    // disable default items ...
    Q_PROPERTY(bool autoFillBackground READ autoFillBackground DESIGNABLE false)
    Q_PROPERTY(QCursor cursor READ cursor DESIGNABLE false)
    Q_PROPERTY(Qt::LayoutDirection layoutDirection READ layoutDirection DESIGNABLE false)
    Q_PROPERTY(bool enabled DESIGNABLE false)
    Q_PROPERTY(QFont font READ font DESIGNABLE false)
    Q_PROPERTY(bool mouseTracking DESIGNABLE false)
    Q_PROPERTY(bool tabletTracking DESIGNABLE false)
    Q_PROPERTY(QLocale locale DESIGNABLE false)
    Q_PROPERTY(QString styleSheet READ styleSheet DESIGNABLE false)
    Q_PROPERTY(QSizePolicy sizePolicy READ sizePolicy DESIGNABLE false)
//    Q_PROPERTY(QRect geometry READ geometry DESIGNABLE false)
    Q_PROPERTY(QSize minimumSize READ minimumSize DESIGNABLE false)
    Q_PROPERTY(QSize maximumSize READ maximumSize DESIGNABLE false)
    Q_PROPERTY(QSize sizeIncrement READ sizeIncrement DESIGNABLE false)
    Q_PROPERTY(QSize baseSize READ baseSize DESIGNABLE false)
    Q_PROPERTY(Qt::FocusPolicy focusPolicy READ focusPolicy DESIGNABLE false)
    Q_PROPERTY(Qt::ContextMenuPolicy contextMenuPolicy READ contextMenuPolicy DESIGNABLE false)
    Q_PROPERTY(QString toolTip READ toolTip DESIGNABLE false)
    Q_PROPERTY(QString toolTipDuration READ toolTipDuration DESIGNABLE false)
    Q_PROPERTY(QString statusTip READ statusTip DESIGNABLE false)
    Q_PROPERTY(QString whatsThis DESIGNABLE false)
    Q_PROPERTY(QString accessibleName READ accessibleName DESIGNABLE false)
    Q_PROPERTY(QString accessibleDescription READ accessibleDescription DESIGNABLE false)
    Q_PROPERTY(bool acceptDrops READ acceptDrops DESIGNABLE false)
    Q_PROPERTY(Qt::InputMethodHints inputMethodHints READ inputMethodHints DESIGNABLE false)
    Q_PROPERTY(QPalette palette READ palette DESIGNABLE false)
    
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit PopupMenu(QWidget *parent = nullptr);

    QColor color() const { return color_; }
    
    void setColor(const QColor& color);
    void setColor(int r, int g, int b);
    
signals:
    
public slots:

private:
    QColor color_;
    
protected:
    void paintEvent(QPaintEvent *evt);
    void resizeEvent(QResizeEvent *evt);
};

#endif
