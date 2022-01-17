#include "qpixmapcombobox.h"
#include "qpixmapcomboboxitem.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QStylePainter>
#include <QStyleOptionComboBox>
#include <QListWidget>
#include <QMenu>
#include <QVBoxLayout>
#include <QPixmap>
#include <QDir>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

QPixmapComboBox::QPixmapComboBox(QWidget *parent)
    : QWidget{parent}
{
    mListWidget = new QListWidget(this);
    mListWidget->setMinimumHeight(250);
    mListWidget->setMaximumHeight(250);

    mCurrentItem = nullptr;

    mMenu = new QMenu(this);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(mListWidget);
    vbox->setSpacing(0);
    mMenu->setLayout(vbox);

}

void QPixmapComboBox::loadImagesFromDirectory(const QString &directory)
{
    QDir imagesDir(directory);
    imagesDir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    const int nImages = int(imagesDir.count());
    for(int iImg = 0; iImg < nImages; iImg++){
        QString filePath = directory + "/"+ imagesDir[iImg];
        if(isImage(filePath)){
            QFileInfo finfo(filePath);

            QPixmapComboBoxItem *comboItem = new QPixmapComboBoxItem(this);
            comboItem->setText(finfo.fileName());
            comboItem->setPixmap(QPixmap(finfo.filePath()));
            addItem(comboItem);
        }
    }
}

void QPixmapComboBox::addItem(QPixmapComboBoxItem *item)
{
    connect(item, &QPixmapComboBoxItem::selected, this, &QPixmapComboBox::onItemSelected);

    QListWidgetItem *imgItem = new QListWidgetItem;
    mListWidget->addItem(imgItem);
    mListWidget->setItemWidget(imgItem, item);
}

void QPixmapComboBox::mousePressEvent(QMouseEvent *e)
{
    mListWidget->setMinimumWidth(width());
    mListWidget->setMaximumWidth(width());
    QPoint p = parentWidget()->mapToGlobal(pos());
    p.setY(p.y() + height());
    mMenu->popup(p);
    QWidget::mousePressEvent(e);
}

void QPixmapComboBox::paintEvent(QPaintEvent *e)
{
    QStylePainter painter(this);
    QStyleOptionComboBox option;
    option.initFrom(this);
    painter.drawComplexControl(QStyle::CC_ComboBox,option);
    if(mCurrentItem){
        painter.drawText(10, rect().center().y() + height()/4, mCurrentItem->text());

    }
    QWidget::paintEvent(e);

}

bool QPixmapComboBox::isImage(const QString &filePath) const
{
    QFile JSFile(":/imageFormats.json");
    if(JSFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QJsonDocument doc = QJsonDocument::fromJson(JSFile.readAll());
        JSFile.close();
        QJsonArray formatsArray = doc.array();
        const int nFormats = formatsArray.size();

        for(int ix = 0; ix < nFormats; ix++){
            if(filePath.endsWith(formatsArray.at(ix).toString(), Qt::CaseInsensitive)){
                return true;
            }
        }
    }
    return false;
}

void QPixmapComboBox::onItemSelected(QPixmapComboBoxItem *item)
{
    mCurrentItem = item;
    emit itemActivated(mCurrentItem);
    update();
    mMenu->hide();
}







