#include "qpixmappopup.h"

#include <QTimer>
#include <QMouseEvent>

QPixmapPopUp::QPixmapPopUp(QWidget *parent)
    : QLabel{parent}
{
    setFrameShape(QLabel::Box);
    setWindowFlags(Qt::Popup);// convertir de tipo ventana popUp
    setFocusPolicy(Qt::WheelFocus);
    mTimer = new QTimer(this);
    mTimer->setSingleShot(true);

    connect(mTimer, &QTimer::timeout, this, [&](){
        hide();
    });
}

void QPixmapPopUp::show(int msecs)
{
    QLabel::show();
    mTimer->start(msecs);
}

void QPixmapPopUp::mousePressEvent(QMouseEvent *e)
{
    emit clicked();
    hide();
    QLabel::mousePressEvent(e);
}
