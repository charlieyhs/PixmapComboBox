#ifndef QPIXMAPPOPUP_H
#define QPIXMAPPOPUP_H

#include <QLabel>
//#include <QMouseEvent>

class QTimer;

class QPixmapPopUp : public QLabel
{
    Q_OBJECT
public:
    QPixmapPopUp(QWidget *parent = nullptr);
    void show(int msecs = 1000);
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent *e)override;
private:
    QTimer *mTimer;
};

#endif // QPIXMAPPOPUP_H
