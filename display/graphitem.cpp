#include "display/graphitem.h"
#include <QCursor>
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <iostream>

GraphItem::GraphItem(QString imageName, QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    imageFileName = imageName;
    mapNode = new Node();
    mapNode->setLatitude(-1);
    mapNode->setLongitude(-1);
    mapNode->setAltitude(-1);

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

void GraphItem::displayInfo(QPoint pos) {
    QWidget* popup = new QWidget();
    popup->move(this->pos().x(),this->pos().y());
    QGridLayout* popupLayout = new QGridLayout(popup);
    QPushButton* createPathButton = new QPushButton("Créer un chemin");
    QPushButton* destroyButton = new QPushButton("Supprimer l'objet");
    popupLayout->addWidget(createPathButton,5,0,1,-1);
    popupLayout->addWidget(destroyButton,6,0,1,-1);

    // Gestion du node associé
    QLabel* labelName = new QLabel("Nom:");
    QLabel* labelRef = new QLabel("Référence:");
    QLabel* labelAlt = new QLabel("Altitude:");
    QLabel* labelLat = new QLabel("Latitude:");
    QLabel* labelLong = new QLabel("Longitude:");

    QLineEdit* leName = new QLineEdit(mapNode->getName());
    QLineEdit* leRef = new QLineEdit(mapNode->getReference());
    QLineEdit* leAlt = new QLineEdit();
    if(mapNode->getAltitude() >= 0)
        leAlt->setText(QString::number(mapNode->getAltitude()));
    QLineEdit* leLat = new QLineEdit();
    if(mapNode->getLatitude() >= 0)
        leLat->setText(QString::number(mapNode->getLatitude()));
    QLineEdit* leLong = new QLineEdit();
    if(mapNode->getLongitude() >= 0)
        leLong->setText(QString::number(mapNode->getLongitude()));

    popupLayout->addWidget(labelName,0,0,1,1);
    popupLayout->addWidget(labelRef,1,0,1,1);
    popupLayout->addWidget(labelAlt,2,0,1,1);
    popupLayout->addWidget(labelLat,3,0,1,1);
    popupLayout->addWidget(labelLong,4,0,1,1);

    popupLayout->addWidget(leName,0,1,1,1);
    popupLayout->addWidget(leRef,1,1,1,1);
    popupLayout->addWidget(leAlt,2,1,1,1);
    popupLayout->addWidget(leLat,3,1,1,1);
    popupLayout->addWidget(leLong,4,1,1,1);

    popup->move(pos.x()+50,pos.y()+50);
    popup->show();

    connect(createPathButton,SIGNAL(clicked()),this,SLOT(on_createPathButton_clicked()));
    connect(createPathButton,SIGNAL(clicked()),popup,SLOT(close()));
    connect(destroyButton,SIGNAL(clicked()),this,SLOT(deleteLater()));
    connect(destroyButton,SIGNAL(clicked()),popup,SLOT(close()));
    connect(leName,SIGNAL(textChanged(QString)),this,SLOT(setName(QString)));
    connect(leRef,SIGNAL(textChanged(QString)),this,SLOT(setRef(QString)));
    connect(leAlt,SIGNAL(textChanged(QString)),this,SLOT(setAlt(QString)));
    connect(leLat,SIGNAL(textChanged(QString)),this,SLOT(setLat(QString)));
    connect(leLong,SIGNAL(textChanged(QString)),this,SLOT(setLong(QString)));
}

void GraphItem::setType(QString t)
{
    mapNode->setType(t);
}

void GraphItem::setName(QString n)
{
    mapNode->setName(n);
}

void GraphItem::setRef(QString r)
{
    mapNode->setReference(r);
}

void GraphItem::setAlt(QString a)
{
    mapNode->setAltitude(a.toFloat());
}

void GraphItem::setLat(QString l)
{
    mapNode->setLatitude(l.toFloat());
}

void GraphItem::setLong(QString l)
{
    mapNode->setLongitude(l.toFloat());
}

void GraphItem::on_createPathButton_clicked()
{
    emit startCreatePath(mapNode->getReference(),this->pos().toPoint());
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
    dataStream << QPoint(hotSpot)
               << mapNode->getName()
               << mapNode->getReference()
               << mapNode->getType()
               << QString::number(mapNode->getAltitude())
               << QString::number(mapNode->getLatitude())
               << QString::number(mapNode->getLongitude());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/IHMMapEditor", itemData);
    mimeData->setText(imageFile());

    QImage image(imageFile());
    QDrag *drag = new QDrag(event->widget());
    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap::fromImage(image).scaled(50, 50));
    drag->setHotSpot(QPoint(drag->pixmap().width()/2 + hotSpot.x(),
                            drag->pixmap().height()/2 + hotSpot.y()));
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
