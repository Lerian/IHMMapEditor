#include "display/mapgraphicsview.h"

MapGraphicsView::MapGraphicsView(QObject *parent) :
    QGraphicsView(dynamic_cast<QWidget*>(parent))
{
    setAcceptDrops(true);
}



void MapGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/IHMMapEditor")) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void MapGraphicsView::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/IHMMapEditor")) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void MapGraphicsView::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/IHMMapEditor")) {
        GraphItem* doorItem = new GraphItem(event->mimeData()->text());
        doorItem->setPos(event->pos());
        this->scene()->addItem(doorItem);

        /*const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/IHMMapEditor");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;
        GraphItem *newItem = NULL;

        if (this->childAt(event->pos() - offset) != 0) {
            event->ignore();
        } else {
            newItem = new GraphItem(event->mimeData()->, this);
            newItem->move(event->pos() - offset);
            newItem->show();
            newItem->setAttribute(Qt::WA_DeleteOnClose);
        }*/

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void MapGraphicsView::mousePressEvent(QMouseEvent *event)
{
    GraphItem *child = dynamic_cast<GraphItem*>(childAt(event->pos()));
    if (!child)
        return;

    QPoint hotSpot = event->pos() - child->pos().toPoint();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QPoint(hotSpot);

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/IHMMapEditor", itemData);
    mimeData->setText(child->imageFile());

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap(child->imageFile()));
    drag->setHotSpot(hotSpot);

    child->hide();

    if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
        ;//child->close();
    else
        child->show();
}
