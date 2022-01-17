#include "qpixmapcomboboxitem.h"
#include "qpixmappopup.h"
#include <QLabel>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QStylePainter>
#include <QStyleOptionButton>

QPixmapComboBoxItem::QPixmapComboBoxItem(QWidget *parent)
    : QWidget{parent}
{
    mPopup = new QPixmapPopUp(this);

    connect(mPopup, &QPixmapPopUp::clicked, this, [&](){
        emit selected(this);
    });
}

QPixmapComboBoxItem::QPixmapComboBoxItem(const QString &text, const QPixmap &pixmap, QWidget *parent)
    : QPixmapComboBoxItem{parent}
{
    setText(text);
    setPixmap(pixmap);
}

void QPixmapComboBoxItem::setPixmap(const QPixmap &pixmap)
{
    mPixmap = pixmap;
    mPopup->setPixmap(mPixmap.scaled(100,100));
}

QPixmap QPixmapComboBoxItem::pixmap() const
{
    return mPixmap;
}

void QPixmapComboBoxItem::mousePressEvent(QMouseEvent *e)
{
    QPoint p = parentWidget()->parentWidget()->parentWidget()->mapToGlobal(e->pos());
    const int x = p.x();
    const int y = p.y();
    const int w = mPopup->pixmap().width();
    const int h = mPopup->pixmap().height();

    mPopup->setGeometry(x,y,w,h);
    mPopup->show();
    QWidget::mousePressEvent(e);
}

void QPixmapComboBoxItem::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawText(2,rect().center().y() + height()/4, mText);
    QWidget::paintEvent(e);
}
