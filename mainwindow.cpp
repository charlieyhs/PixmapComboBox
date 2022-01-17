#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpixmapcomboboxitem.h"
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->addItem(new QPixmapComboBoxItem("red", makePixmapFromColor(Qt::red)));
    ui->comboBox->addItem(new QPixmapComboBoxItem("verde", makePixmapFromColor(Qt::green)));
    ui->comboBox->addItem(new QPixmapComboBoxItem("blue", makePixmapFromColor(Qt::blue)));
    ui->comboBox->loadImagesFromDirectory("C:/Users/MARTHA/Desktop/imagenes");

    ui->comboBox->setMinimumHeight(ui->comboBox->height());
    ui->comboBox->setMaximumHeight(ui->comboBox->height());

    connect(ui->comboBox, &QPixmapComboBox::itemActivated, this, [&](QPixmapComboBoxItem *item){
       ui->label->setPixmap(item->pixmap()) ;
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

QPixmap MainWindow::makePixmapFromColor(const QColor &color) const
{
    QImage img(250,250,QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&img);
    painter.fillRect(0,0,250,250,color);

    return QPixmap::fromImage(img);
}

