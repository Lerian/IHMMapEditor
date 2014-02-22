#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#include <QGraphicsObject>
#include "node.h"

class GraphItem : public QGraphicsObject
{
    Q_OBJECT

    QString imageFileName;
    Node* mapNode;

public:
    explicit GraphItem(QString imageName, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QString imageFile() const;

    void displayInfo();

    Node* getNode() {return mapNode;}
    QString getType() {return mapNode->getType();}

public slots:
    void setType(QString t);
    void setName(QString n);
    void setRef(QString r);
    void setAlt(QString a);
    void setLat(QString l);
    void setLong(QString l);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    
};

#endif // GRAPHITEM_H
