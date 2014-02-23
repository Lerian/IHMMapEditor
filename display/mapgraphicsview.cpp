#include "display/mapgraphicsview.h"

MapGraphicsView::MapGraphicsView(QObject *parent) :
    QGraphicsView(dynamic_cast<QWidget*>(parent))
{
    setAcceptDrops(true);

    floor = new Floor();
    drawPath = false;
    lastLine = NULL;
}

MapGraphicsView::MapGraphicsView(QString name, QObject *parent) :
    QGraphicsView(dynamic_cast<QWidget*>(parent))
{
    setAcceptDrops(true);

    floor = new Floor();
    floor->setName(name);
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

        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/IHMMapEditor");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPoint offset;
        QString nodeName;
        QString nodeRef;
        QString nodeType;
        QString nodeAlt;
        QString nodeLat;
        QString nodeLong;
        dataStream >> offset
                   >> nodeName
                   >> nodeRef
                   >> nodeType
                   >> nodeAlt
                   >> nodeLat
                   >> nodeLong;

        doorItem->setType(nodeType);
        doorItem->setName(nodeName);
        doorItem->setRef(nodeRef);
        doorItem->setAlt(nodeAlt);
        doorItem->setLat(nodeLat);
        doorItem->setLong(nodeLong);

        doorItem->setPos(mapToScene(event->pos()-offset));
        this->scene()->addItem(doorItem);

        connect(doorItem,SIGNAL(startCreatePath(QString,QPoint)),this,SLOT(createPath(QString,QPoint)));

        /*const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/IHMMapEditor");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPoint offset;
        dataStream >> offset;
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
    GraphItem *child = dynamic_cast<GraphItem*>(scene()->itemAt(mapToScene(event->pos())));
    if (!child) {
        return;
    }

    if(event->button() == Qt::RightButton) {
        child->displayInfo(event->pos());
    } else {
        if(!drawPath) {
            QPoint hotSpot = mapToScene(event->pos()).toPoint() - child->pos().toPoint();

            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << QPoint(hotSpot)
                       << child->getNode()->getName()
                       << child->getNode()->getReference()
                       << child->getNode()->getType()
                       << QString::number(child->getNode()->getAltitude())
                       << QString::number(child->getNode()->getLatitude())
                       << QString::number(child->getNode()->getLongitude());

            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/IHMMapEditor", itemData);
            mimeData->setText(child->imageFile());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setPixmap(QPixmap(child->imageFile()).scaled(50, 50));
            drag->setHotSpot(QPoint(drag->pixmap().width()/2 + hotSpot.x(),
                                    drag->pixmap().height()/2 + hotSpot.y()));
            child->hide();

            if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
                child->deleteLater();
            else
                child->show();
        } else {
            if(lastLine != NULL) {
                scene()->removeItem(lastLine);
            }
            if(child->pos().toPoint() != pathStart) {
                QPoint scenePos = child->pos()/*mapToScene(event->pos())*/.toPoint();
                lastLine = new QGraphicsLineItem(pathStart.x(),pathStart.y(),scenePos.x(),scenePos.y());
                lastLine->setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                lastLine->setEnabled(false);
                scene()->addItem(lastLine);

                drawPath = false;
                lastLine = NULL;
            } else {

                drawPath = false;
                lastLine = NULL;
            }
        }
    }
}

void MapGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(drawPath) {
        if(lastLine != NULL) {
            scene()->removeItem(lastLine);
        }
        QPoint scenePos = mapToScene(event->pos()).toPoint();
        lastLine = new QGraphicsLineItem(pathStart.x(),pathStart.y(),scenePos.x(),scenePos.y());
        lastLine->setEnabled(false);
        scene()->addItem(lastLine);
    }
}

void MapGraphicsView::createPath(QString ref, QPoint pos)
{
    drawPath = true;
    pathStart = pos;
}
