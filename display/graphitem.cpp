#include "display/graphitem.h"
#include <QCursor>
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

GraphItem::GraphItem(QString imageName, QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    imageFileName = imageName;

    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptDrops(false);
}

QRectF GraphItem::boundingRect() const
{
    return QRectF(-25, -25, 50, 50);
}

void GraphItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF target(this->boundingRect());
    QImage image(this->imageFile());

    painter->drawImage(target, image);
}

QString GraphItem::imageFile() const
{
    return imageFileName;
}

void GraphItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
}

void GraphItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
}

void GraphItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
}

void GraphItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::ClosedHandCursor);
}

void GraphItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
    .length() < QApplication::startDragDistance()) {
        return;
    }

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);

    QImage image(imageFile());
    mime->setImageData(image);

    drag->setPixmap(QPixmap::fromImage(image).scaled(30, 40));
    drag->setHotSpot(QPoint(15, 30));

    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

void GraphItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::OpenHandCursor);
}
