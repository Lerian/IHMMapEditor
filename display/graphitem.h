#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#include <QGraphicsObject>

class GraphItem : public QGraphicsObject
{
    Q_OBJECT

    QString imageFileName;

public:
    explicit GraphItem(QString imageName, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QString imageFile() const;

    void displayInfo();

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    
};

#endif // GRAPHITEM_H
