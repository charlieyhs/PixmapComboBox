#ifndef QPIXMAPCOMBOBOXITEM_H
#define QPIXMAPCOMBOBOXITEM_H

#include <QWidget>
#include <QPixmap>

class QPixmapPopUp;

class QPixmapComboBoxItem : public QWidget
{
    Q_OBJECT
public:
    QPixmapComboBoxItem(QWidget *parent = nullptr);
    QPixmapComboBoxItem(const QString &text,
                        const QPixmap &pixmap,
                        QWidget *parent = nullptr);

    void setPixmap(const QPixmap &pixmap);
    QPixmap pixmap() const;

    QString text()const{
        return mText;
    }
    void setText(const QString text){
        mText = text;
    }
signals:
    void selected(QPixmapComboBoxItem *item);
protected:
    void mousePressEvent(QMouseEvent *e)override;
    void paintEvent(QPaintEvent *e)override;
private:
    QPixmapPopUp *mPopup;
    QString mText;
    QPixmap mPixmap;

};

#endif // QPIXMAPCOMBOBOXITEM_H
