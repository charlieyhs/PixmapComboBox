#ifndef QPIXMAPCOMBOBOX_H
#define QPIXMAPCOMBOBOX_H

#include <QWidget>

class QMenu;
class QListWidget;
class QPixmapComboBoxItem;

class QPixmapComboBox : public QWidget
{
    Q_OBJECT
public:
    QPixmapComboBox(QWidget *parent = nullptr);

    QPixmapComboBoxItem *currentItem()const{
        return mCurrentItem;
    }
    void loadImagesFromDirectory(const QString &directory);
    void addItem(QPixmapComboBoxItem *item);
signals:
    void itemActivated(QPixmapComboBoxItem *item);

protected:
    void mousePressEvent(QMouseEvent *e)override;
    void paintEvent(QPaintEvent *e)override;
private:
    QListWidget *mListWidget;
    QMenu *mMenu;
    QPixmapComboBoxItem *mCurrentItem;

    bool isImage(const QString &filePath)const;
    void onItemSelected(QPixmapComboBoxItem *item);
};

#endif // QPIXMAPCOMBOBOX_H
