#ifndef MAPGRAPHICSVIEW_H
#define MAPGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include "graphitem.h"
#include <iostream>
#include "floor.h"

class MapGraphicsView : public QGraphicsView
{
    Q_OBJECT

    Floor* floor;

public:
    explicit MapGraphicsView(QObject *parent = 0);
    explicit MapGraphicsView(QString name, QObject *parent = 0);

    Floor* getFloor() {return floor;}
    
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    
public slots:
    
};

#endif // MAPGRAPHICSVIEW_H
