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

void GraphItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
}

void GraphItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
    .length() < QApplication::startDragDistance()) {
        return;
    }

    QPoint hotSpot = event->pos().toPoint();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QPoint(hotSpot);

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/IHMMapEditor", itemData);

    QImage image(imageFile());
    QDrag *drag = new QDrag(event->widget());
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap::fromImage(image).scaled(50, 50));
    drag->setHotSpot(hotSpot);
    /*
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);

    QImage image(imageFile());
    mime->setImageData(image);

    drag->setPixmap(QPixmap::fromImage(image).scaled(50, 50));
    drag->setHotSpot(QPoint(15, 30));
*/
    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

void GraphItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::OpenHandCursor);
}
